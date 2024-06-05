#include <filesystem>
#include <iostream>
#include <array>
#include <string>
#include <locale>
#include <system_error>

#include "dem_manager.h"

#include <opencv2/imgproc.hpp>
#include <oneapi/tbb/parallel_for_each.h>
#include <oneapi/tbb/parallel_sort.h>

dem_manager::dem_manager() : con(fmt::format("dbname=dem_db user=postgres password=gitr&d123! hostaddr=175.116.181.25 port=5432"))
{
	pqxx::work w(con);
	std::string query = fmt::format("SELECT 1 FROM {} LIMIT 1", table_name);
	pqxx::result R = w.exec(query);

	if (R.empty())
		initialize(w);
	else
		std::cout << "DEMs were already inserted in DB......" << '\n';
}

dem_manager::~dem_manager()
{
	// pqxx에서 자동으로 닫아준다.
	/*if (con.is_open())
		con.close();*/
}

void dem_manager::update_progress_percentage(std::atomic<int>& progress, int total_tasks)
{
	int completed = progress.load();
	int percentage = (completed * 100) / total_tasks;

	std::cout << "\rDEMs loading... : " << percentage << "%";
	std::cout.flush();
}

void dem_manager::initialize(pqxx::work& wk)
{
	//std::filesystem::directory_iterator("D:\DEM_2021y_5m(img)") 경로 설정
	std::vector<std::filesystem::path> dem_paths;

	for (const auto& dem_file : std::filesystem::directory_iterator("/dems"))
	{
		if (dem_file.path().extension() != ".img")
			continue;

		dem_paths.emplace_back(dem_file.path());
	}
	
	std::atomic<int> progress(0);
	const int num_tasks = dem_paths.size();

	tbb::parallel_for_each(dem_paths.begin(), dem_paths.end(), [this, &progress, &num_tasks](const std::filesystem::path& dem_path)->void
		{
			demv2 single_dem(dem_path);

			if (is_useless_dem(single_dem))
				return;

			const cv::Point2d& lt = single_dem.left_top;
			const cv::Point2d rb
			(
				lt.x + single_dem.delta.x * single_dem.dem_size.width,
				lt.y + single_dem.delta.y * single_dem.dem_size.height
			);

			const area dem_area(cv::Point2d(lt.x, rb.y), cv::Point2d(rb.x, lt.y));
			dems.insert(std::make_pair(dem_area, single_dem));
			decltype(dems)::key_compare compare = dems.key_comp();

			++progress;
			update_progress_percentage(progress, num_tasks);
		});
	//최종 로딩
	update_progress_percentage(progress, num_tasks);
	std::cout << '\n';

	{
		std::vector<std::tuple<area, demv2>> sorter(dems.begin(), dems.end());
		decltype(dems) swapper;
		
		std::sort(sorter.begin(), sorter.end(), [](decltype(sorter)::const_reference lhs, decltype(sorter)::const_reference rhs)->bool
			{
				const auto& [boundary_lhs, dem_lhs] = lhs;
				const auto& [boundary_rhs, dem_rhs] = rhs;

				return boundary_lhs < boundary_rhs;
			});

		for (const auto& [boundary, single_dem] : sorter)
			swapper.insert(std::make_pair(boundary, single_dem));

		dems = swapper;
	}

	//db에 insert를 한번만 실행함(모든 값들을 벡터에 담아놓고 문자열 합치기)
	short primary_key = 0;
	std::vector<std::string> values;
	for (const auto& kv : dems)
	{
		const auto& [boundary, single_dem] = kv;
		const auto& [min, max] = boundary;

		values.push_back(fmt::format("({}, box\'(({},{}),({},{}))\', \'{}\')",
			primary_key, min.x, min.y, max.x, max.y, single_dem.abs_path.generic_string()));
		++primary_key;
	}
	if (!values.empty()) {
		//pqxx::work wk(con);
		const std::string insert_query = fmt::format("INSERT INTO {} (idx, boundary, dem_file) VALUES ", table_name) +
			std::accumulate(std::next(values.begin()), values.end(), values[0],
				[](std::string a, std::string b) { return a + ", " + b; });

		wk.exec(insert_query);
		wk.commit();
	}

	oneapi::tbb::concurrent_vector<std::map<std::string, size_t>> cv_points_diagnosis;
	for (const auto& [boundary, single_dem] : dems)
	{
		tg.run([this, &single_dem, &cv_points_diagnosis]()->void
			{
				auto diagnosis = diagnose_dem(single_dem);
				cv_points_diagnosis.push_back(diagnosis);
			});
	}
	tg.wait();

	decltype(cv_points_diagnosis)::value_type total_diagnosis;
	std::string status[5]{ "total", "non-positives", "nans", "infs", "normals" };
	for (const auto& state : status)
		total_diagnosis.emplace(state, 0ULL);

	for (const auto& diagnosis : cv_points_diagnosis)
		for (const auto& [state, points] : diagnosis)
			total_diagnosis[state] += points;

	for (const auto& [state, points] : total_diagnosis)
		std::cout << fmt::format("{} : {} points\n", state, points);
}

bool dem_manager::is_useless_dem(const demv2& dem_obj) const
{
	const cv::Mat& dem_mat = dem_obj.dem_matrix;
	cv::Mat mask(dem_mat.size(), CV_8U);

	dem_mat.forEach<float>([&mask](float& elem, const int indices[2])->void
		{
			if (elem <= 0.0 or std::isnan(elem) or std::isinf(elem))
				static_cast<uchar* const>(static_cast<void* const>(mask.data))[mask.cols * indices[0] + indices[1]] = '\x01';
			else
				static_cast<uchar* const>(static_cast<void* const>(mask.data))[mask.cols * indices[0] + indices[1]] = '\x00';
		});
	if (cv::countNonZero(mask) == mask.size.dims())
		return true;

	return false;
}

bool dem_manager::is_complete_dem(const demv2& dem_obj) const
{
	const cv::Mat& dem_mat = dem_obj.dem_matrix;
	cv::Mat mask = dem_mat > 0.0;

	if (cv::countNonZero(mask) == mask.size.dims())
		return true;

	return false;
}

std::map<std::string, size_t> dem_manager::diagnose_dem(const demv2& dem_obj) const
{
	const cv::Mat& dem_mat = dem_obj.dem_matrix;

	std::map<std::string, size_t> diagnosis;

	const size_t total = dem_mat.size().area();
	diagnosis.emplace("total", dem_mat.size().area());

	const size_t np_count = cv::countNonZero(dem_mat <= 0.0);
	if (np_count > 0)
		diagnosis.emplace("non-positives", np_count);

	const size_t nan_count = cv::countNonZero(dem_mat != dem_mat);
	if (nan_count > 0)
		diagnosis.emplace("nans", nan_count);

	const size_t inf_count = cv::countNonZero(dem_mat == std::numeric_limits<float>::infinity());
	if (inf_count > 0)
		diagnosis.emplace("infs", inf_count);

	diagnosis.emplace("normals", total - np_count - nan_count - inf_count);

	return diagnosis;
}

std::vector<dem_manager::dem_row> dem_manager::select_query(std::string where_clause) const
{
	//pqxx::connection con = connect();
	pqxx::work w(con);

	const std::string query = fmt::format("SELECT * FROM {} WHERE {}" , table_name, where_clause);
	pqxx::result query_result = w.exec(query);

	std::vector<dem_row> rows;
	for (const auto& row_result : query_result)
	{
		dem_row row;
		std::unordered_map<std::string, std::function<void(const pqxx::const_row_iterator::reference&)>> behavior
		{
			{ "idx", [&row](const pqxx::const_row_iterator::reference& field)->void { row.idx = field.as<unsigned short>(); }},
			{ "boundary", [&row](const pqxx::const_row_iterator::reference& field)->void
				{
					char dump;
					std::istringstream(field.c_str()) >>
						dump >> row.boundary.max.x >> dump >> row.boundary.max.y >> dump >> dump >>
						dump >> row.boundary.min.x >> dump >> row.boundary.min.y >> dump;
				}
			},
			{ "dem_file", [&row](const pqxx::const_row_iterator::reference& field)->void { row.dem_path = field.c_str(); }}
		};

		for (const auto& field : row_result)
		{
			if (not behavior.contains(field.name()))
				continue;

			behavior.at(field.name())(field);
		}
		rows.emplace_back(row);
	}

	//con.close();
	return rows;
}

void dem_manager::insert_query(const dem_row& target) const
{
	//pqxx::connection con = connect();
	pqxx::work w(con);

	const auto& [idx, boundary, dem_path] = target;
	const std::string query = fmt::format
	(
		"INSERT INTO {} (idx, boundary, dem_file) VALUES({}, box\'(({},{}),({},{}))\', \'{}\')",
		table_name,
		idx,
		boundary.min.x,
		boundary.min.y,
		boundary.max.x,
		boundary.max.y,
		dem_path.generic_string()
	);

	const auto result = w.exec(query);
	if (result.inserted_oid() != pqxx::oid_none)
	{
		// error process...
	}
	w.commit();

	//con.close();
}

double dem_manager::find_ground_height(const double& x, const double& y) const
{
	const auto find_from_memory = [this](const double& x, const double& y)->std::vector<decltype(preload_dem_cache)::const_iterator>
		{
			std::vector<decltype(preload_dem_cache)::const_iterator> results;

			for (auto preload_dem = preload_dem_cache.begin(); preload_dem != preload_dem_cache.end(); ++preload_dem)
			{
				preload_dem = std::find_if(preload_dem, preload_dem_cache.end(), [&x, &y](decltype(preload_dem_cache)::const_reference area_dem)->bool
					{
						const auto& [area, dem] = area_dem;
						return area.contains(x, y);
					});

				if (preload_dem == preload_dem_cache.end())
					break;

				results.emplace_back(preload_dem);
			}
			return results;
		};

	auto target_dems = find_from_memory(x, y);
	if (target_dems.empty())
	{
		auto selected_rows = select_query(fmt::format("boundary @> point\'({}, {})\'", x, y));
		if (selected_rows.empty())
			return std::nan("no reference dem");

		for (const auto& [index, boundary, path] : selected_rows)
			preload_dem_cache.emplace(std::make_pair(boundary, demv2(path)));

		target_dems = find_from_memory(x, y);
		if (target_dems.empty())
			return nan("no reference dem");
	}
	std::vector<double> reasonable_altitudes;
	for (const auto& target_dem : target_dems)
	{
		const auto& [boundary, dem] = *target_dem;
		reasonable_altitudes.emplace_back(dem.find_ground_height(x, y));
	}

	std::erase_if(reasonable_altitudes, [](const double& altitude)->bool { return std::isnan(altitude) or std::isinf(altitude) or altitude < 0.0; });
	return std::accumulate(reasonable_altitudes.begin(), reasonable_altitudes.end(), 0.0, std::plus<double>()) / reasonable_altitudes.size();
}