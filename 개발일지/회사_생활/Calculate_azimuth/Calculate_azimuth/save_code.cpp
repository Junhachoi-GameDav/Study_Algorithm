//// std
//#include <iostream>
//#include <filesystem>
//#include <span>
//#include <regex>
//
//// opencv
//#include <opencv2/opencv.hpp>
//
//// Exiv2
//#include <exiv2/exiv2.hpp>
//
//// proj4
//#include <proj.h>
//
//// oneTBB
//#include <oneapi/tbb/parallel_for.h>
//#include <oneapi/tbb/parallel_for_each.h>
//#include <oneapi/tbb/concurrent_vector.h>
//
//#pragma region ��/�浵 ��ǥ�� EPSG:5186���� ��ȯ -> Proj ���
//
///** transform
//* @brief	- proj ���̺귯��(9.x.x ���� �̻�)�� ����Ͽ� ��Ÿ�������� ��/�浵 ��ǥ�� EPSG:5186���� ��ȯ�Ѵ�.
//* @param	- ��Ÿ������ std::span<double>
//* @return	- �浵, ����, ��
//*/
//std::array<double, 3> transform(const std::span<double>& s)
//{
//	assert(s.size() <= 3);
//
//	std::unique_ptr<PJ_CONTEXT, decltype((void(*)(PJ_CONTEXT*))(proj_context_destroy))> ctx(proj_context_create(), (void(*)(PJ_CONTEXT*))(proj_context_destroy));
//	std::shared_ptr<PJ> trans_obj
//	(
//		proj_create_crs_to_crs
//		(
//			ctx.get(),
//			"+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs",
//			"+proj=tmerc +lat_0=38 +lon_0=127 +k=1 +x_0=200000 +y_0=600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs",
//			nullptr
//		),
//		proj_destroy
//	);
//	// from src to dst
//	PJ_COORD from = proj_coord(s[1], s[0], s[2], 0.0); //�浵, ����, ��
//	PJ_COORD to = proj_trans(trans_obj.get(), PJ_DIRECTION::PJ_FWD, from);
//
//	return { to.xyz.x, to.xyz.y, to.xyz.z };
//}
//
//#pragma endregion
//
//#pragma region ��Ÿ������ �ް� ��ȯ -> Exiv2 ���
//
///** convert_rational_to_decimal
//* @brief	- �м��� �Ҽ��� ��ȯ
//* @param	- rational �浵 or ����
//*/
//double convert_rational_to_decimal(const Exiv2::Rational& rational)
//{
//	if (rational.second == 0)
//		return 0.0;
//	return static_cast<double>(rational.first) / static_cast<double>(rational.second);
//}
//
///** convert_gps_lon_lat
//* @brief	- �浵, ���� �������� ��ȯ
//* @param	- value �浵 or ���� ��Ÿ������
//*/
//double convert_gps_lon_lat(const Exiv2::Value& value)
//{
//	const double degrees = convert_rational_to_decimal(value.toRational(0));
//	const double minutes = convert_rational_to_decimal(value.toRational(1));
//	const double seconds = convert_rational_to_decimal(value.toRational(2));
//
//	return degrees + minutes / 60.0 + seconds / 3600.0;
//}
//
///** convert_gps_alt
//* @brief	- �� double�� ��ȯ
//* @param	- value ��
//*/
//double convert_gps_alt(const Exiv2::Value& value)
//{
//	const double altitude = convert_rational_to_decimal(value.toRational(0));
//
//	return altitude;
//}
//
///** read_meta_data
//* @brief		- �̹��� ��θ� �޾� ��Ÿ�����͸� �о�� �� ��ȯ�Ѵ�.
//* @param	- img_path �̹��� ���
//* @return	- cur_value ����, �浵, ��
//*/
//std::array<double, 3> read_meta_data(const std::string& img_path)
//{
//	assert(std::filesystem::exists(img_path));
//
//	const std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open(img_path);
//
//	image->readMetadata();
//
//	const Exiv2::ExifData& exifData = image->exifData();
//
//	std::array<double, 3> cur_value{};
//	int num = 0;
//	for (const auto& data : exifData)
//	{
//		if (data.tagName() == "GPSLatitude" || data.tagName() == "GPSLongitude")
//		{
//			const Exiv2::Value& value = data.value();
//			cur_value[num] = convert_gps_lon_lat(value);
//			std::cout << std::format("{} = {}\n", data.tagName(), cur_value[num]);
//			num++;
//			continue;
//		}
//		if (data.tagName() == "GPSAltitude")
//		{
//			const Exiv2::Value& value = data.value();
//			cur_value[num] = convert_gps_alt(value);
//			std::cout << std::format("{} = {}\n", data.tagName(), cur_value[num]);
//		}
//	}
//
//	return cur_value;
//}
//
//#pragma endregion
//
//#pragma region ������ǥ ������ǥ�� ��ȯ -> opencv ���
//
///** change_video_to_img
//* @brief		- ������ǥ �̹�����ǥ�� ��ȯ
//* @brief		- ī�޶� ���� 9248 x 6944 pixels  0.7 ����ũ�ι��� ��ġ(0.0000007 ����), (4608 x 3456 ���� = 2,304 ~ -2,304 x 1,728 ~ -1,728)
//* @param	- my_client ����, img_path �̹��� ���
//* @return	- photo_points �̹��� ��ǥ
//*/
//cv::Mat_<double> change_video_to_img(const cv::Mat& image)
//{
//	const int img_width = image.cols;
//	const int img_height = image.rows;
//
//	constexpr double focal_length = 4.8;
//	constexpr double pixel_size = 0.0007;
//	constexpr double focal_length_in_pixel = focal_length / pixel_size;
//
//	const cv::Mat vision_to_photo = (cv::Mat_<double>(3, 3) <<
//		1.0, 0.0, -(img_width / 2),
//		0.0, -1.0, (img_height / 2),
//		0.0, 0.0, -focal_length_in_pixel);
//
//	cv::Mat_<double> photo_points(3, 1);
//
//	const cv::Mat pos = (cv::Mat_<double>(3, 1) << img_width / 2, img_height / 2, 1.0);
//
//	photo_points = vision_to_photo * pos;
//
//	return photo_points;
//}
//
//#pragma endregion
//
//#pragma region ������ ���
///** calculate_azimuth
//* @brief		- ������( A to B )�� ���Ѵ�.
//* @param	- Ax, Ay, Bx, By
//* @return	- azimuth
//*/
//double calculate_azimuth(double x1, double y1, double x2, double y2)
//{
//	const double PI = 3.14159265358979323846;
//
//	double deltaX = x2 - x1;
//	double deltaY = y2 - y1;
//	double azimuth = atan2(deltaY, deltaX);
//	azimuth = azimuth * (180 / PI);
//	azimuth = 90 - azimuth; // ����  0����
//
//	if (azimuth < 0)
//		azimuth += 360.0;
//
//	return azimuth;
//}
//
//#pragma endregion
//
//
//int main()
//{
//	namespace fs = ::std::filesystem;
//
//	const std::filesystem::path cur_path = std::filesystem::current_path();
//	const std::filesystem::path img_path = cur_path / "Image20231207-061900" / "IMG_03_0000000005_L.jpg";
//	//const std::filesystem::path img_path0 = cur_path / "Image20231207-061900" / "IMG_03_0000000062_L.jpg";
//	//const std::filesystem::path img_path1 = cur_path / "Image20231207-061900" / "IMG_03_0000000001_L.jpg";
//
//	tbb::concurrent_vector<std::tuple<size_t, cv::Mat>> image_paths;
//	std::regex re("_(\\d+)_L\\.jpg$");
//	tbb::parallel_for_each(fs::directory_iterator(cur_path / "Image20231207-061900"), fs::directory_iterator({}), [&image_paths, &re](const fs::path& path)->void
//		{
//			if (path.extension() != ".jpg")
//				return;
//
//			std::smatch match;
//			const std::string filename = path.filename().generic_string();
//			if (!std::regex_search(filename, match, re))
//				return;
//
//			cv::Mat image = cv::imread(path.generic_string());
//			image_paths.emplace_back(std::forward_as_tuple(std::stoull(match[1].str()), image));
//		});
//
//	std::sort(image_paths.begin(), image_paths.end(), [](const decltype(image_paths)::const_reference lhs, const decltype(image_paths)::const_reference rhs)->bool
//		{
//			const auto& [index_lhs, image_lhs] = lhs;
//			const auto& [index_rhs, image_rhs] = rhs;
//
//			return index_lhs < index_rhs;
//		});
//
//	tbb::concurrent_vector<std::vector<cv::DMatch>> matched_results(image_paths.size() - 1);
//	tbb::parallel_for(0ULL, image_paths.size() - 1ULL, [&image_paths, &matched_results](size_t i)->void
//		{
//			const auto& [index_current, image_current] = image_paths[i];
//			const auto& [index_next, image_next] = image_paths[i + 1];
//			//matched_results[i]= ;
//		});
//
//	std::smatch match;
//
//	std::string filename = img_path.filename().string();
//
//	cv::Mat baseRotation = cv::Mat::eye(3, 3, CV_64F);
//	std::vector<cv::Mat> Rotations;
//
//	if (!std::regex_search(filename, match, re) || match.size() < 1)
//		return 0;
//
//	std::string numStr = match.str(1);
//	int numLength = numStr.length();
//
//	for (int i = 1; i <= std::stoi(numStr); ++i)
//	{
//		std::stringstream ss;
//		ss << std::setw(numLength) << std::setfill('0') << i - 1;
//		std::string cur_filename = std::regex_replace(filename, re, "_" + ss.str() + "_L.jpg");
//		ss.str("");
//		ss.clear();
//		ss << std::setw(numLength) << std::setfill('0') << i;
//		std::string next_filename = std::regex_replace(filename, re, "_" + ss.str() + "_L.jpg");
//
//		std::filesystem::path cur_path = img_path.parent_path() / cur_filename;
//		std::filesystem::path next_path = img_path.parent_path() / next_filename;
//
//		cv::Ptr<cv::ORB> detector = cv::ORB::create(2000);
//
//		cv::Mat cur_image = cv::imread(cur_path.string());
//		cv::Mat next_image = cv::imread(next_path.string());
//
//		if (cur_image.empty() || next_image.empty())
//			return -1;
//
//		std::vector<cv::KeyPoint> keypoint1;
//		std::vector<cv::KeyPoint> keypoint2;
//		cv::Mat des1;
//		cv::Mat des2;
//
//		detector->detectAndCompute(cur_image, cv::noArray(), keypoint1, des1);
//		detector->detectAndCompute(next_image, cv::noArray(), keypoint2, des2);
//
//		cv::Mat detect1;
//		cv::Mat detect2;
//
//		cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING, true);
//
//		std::vector<cv::DMatch> matched;
//		matcher->match(des1, des2, matched);
//
//		// Essential
//		std::vector<cv::Point2f> points1, points2;
//		for (auto& match : matched) {
//			points1.push_back(keypoint1[match.queryIdx].pt);
//			points2.push_back(keypoint2[match.trainIdx].pt);
//		}
//
//		cv::Mat mask;
//		constexpr double focal = 4.8;
//		cv::Point2f photo_mid(cur_image.cols / 2, cur_image.rows / 2);
//		cv::Mat Essential_result = cv::findEssentialMat(points1, points2, focal, photo_mid, cv::RANSAC, 0.999, 1.0, mask);
//
//		// ȸ����(���)
//		cv::Mat Rotation;
//		cv::Mat Translation;
//		cv::recoverPose(Essential_result, points1, points2, Rotation, Translation, focal, photo_mid, mask);
//
//		// ������ ȸ��
//		baseRotation = baseRotation * Rotation;
//		Rotations.push_back(baseRotation);
//
//		std::cout << std::format("#{}\n {} -> {} = \n", i, i - 1, i) << baseRotation << "\n";
//	}
//	/*
//	std::regex re("_(\\d+)_L\\.jpg$");
//	std::smatch match;
//
//	std::string filename = img_path.filename().string();
//	std::vector<std::pair<double, double>> real_pos_vec;
//
//	if (!std::regex_search(filename, match, re) || match.size() < 1)
//		return 0;
//
//	std::string numStr = match.str(1);
//	int numLength = numStr.length();
//	for (int i = 0; i <= std::stoi(numStr); ++i)
//	{
//		std::stringstream ss;
//		ss << std::setw(numLength) << std::setfill('0') << i;
//
//		// ���ο� ���� �̸� ����
//		std::string new_filename = std::regex_replace(filename, re, "_" + ss.str() + "_L.jpg");
//		std::filesystem::path new_path = img_path.parent_path() / new_filename;
//
//		cv::Mat image = cv::imread(img_path.string());
//
//		std::array<double, 3> meta_data = read_meta_data(new_path.string());
//		const std::array<double, 3> img_meta = transform(meta_data);
//		const cv::Mat_<double> ground_meta = (cv::Mat_<double>(3, 1) << img_meta[0], img_meta[1], img_meta[2]);
//
//		const cv::Mat_<double> img_pos = change_video_to_img(image);
//
//		constexpr double Altitude = 20;
//		double lambda = img_pos.at<double>(2, 0) / (Altitude - ground_meta.at<double>(2, 0));
//
//		cv::Mat real_pos = img_pos / lambda;
//		real_pos += ground_meta;
//
//		real_pos_vec.push_back({ real_pos.at<double>(0, 0), real_pos.at<double>(1, 0) } );
//	}
//
//	for (size_t i = 1; i < real_pos_vec.size(); ++i)
//	{
//		auto& current = real_pos_vec[i];
//		auto& previous = real_pos_vec[i - 1];
//
//		auto result =
//			calculate_azimuth
//			(
//				current.first,
//				current.second,
//				previous.first,
//				previous.second
//			);
//		std::cout << "#" << i << "\n";
//		std::cout << std::format("{}  {} \n", previous.first, current.first);
//		std::cout << std::format("{}  {} = {}\n", previous.second, current.second, result) << "\n";
//	}
//	*/
//	/*
//	cv::Ptr<cv::ORB> detector = cv::ORB::create(2000);
//	//cv::ORB;
//	// cv::SIFT;
//	//cv::AKAZE;
//
//	cv::Mat image1 = cv::imread(img_path0.string());
//	cv::Mat image2 = cv::imread(img_path1.string());
//
//	if (image1.empty() || image2.empty())
//		return -1;
//
//	std::vector<cv::KeyPoint> keypoint1;
//	std::vector<cv::KeyPoint> keypoint2;
//	cv::Mat des1;
//	cv::Mat des2;
//
//	detector->detectAndCompute(image1, cv::noArray(), keypoint1, des1);
//	detector->detectAndCompute(image2, cv::noArray(), keypoint2, des2);
//
//	cv::Mat detect1;
//	cv::Mat detect2;
//	cv::drawKeypoints(image1, keypoint1, detect1);
//	cv::resize(detect1, detect1, detect1.size() / 4);
//	cv::imshow("detect 1 result", detect1);
//	cv::waitKey(0);
//	cv::drawKeypoints(image2, keypoint2, detect2);
//	cv::resize(detect2, detect2, detect2.size() / 4);
//	cv::imshow("detect 2 result", detect2);
//	cv::waitKey(0);
//
//	cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING, true);
//	//cv::Ptr<cv::FlannBasedMatcher> matcher = cv::FlannBasedMatcher::create();
//
//	std::vector<cv::DMatch> matched;
//	//std::vector<std::vector<cv::DMatch>> matched;
//	matcher->match(des1, des2, matched);
//
//	cv::Mat result;
//
//	// Fundamental
//	std::vector<cv::Point2f> points1, points2;
//	for (auto& match : matched) {
//		points1.push_back(keypoint1[match.queryIdx].pt);
//		points2.push_back(keypoint2[match.trainIdx].pt);
//	}
//
//	cv::Mat mask;
//	//cv::Mat filtered_result = cv::findFundamentalMat(points1, points2, cv::FM_RANSAC, 3, 0.99, mask);
//
//	// Essential
//	constexpr double focal = 4.8;
//	cv::Point2f photo_mid(image1.cols / 2, image1.rows / 2);
//	cv::Mat Essential_result = cv::findEssentialMat(points1, points2, focal, photo_mid, cv::RANSAC, 0.999, 1.0, mask);
//
//	// ȸ����(���)
//	cv::Mat Rotation;
//	cv::Mat Translation;
//	auto test = cv::recoverPose(Essential_result, points1, points2, Rotation, Translation, focal, photo_mid, mask);
//
//	cv::drawMatches(image1, keypoint1, image2, keypoint2, matched, Essential_result);
//	cv::resize(Essential_result, Essential_result, Essential_result.size() / 4);
//	cv::imshow("matched result", Essential_result);
//	cv::waitKey(0);
//
//	//std::cout << Rotation << "\n";
//	//std::cout << Translation << "\n";
//
//	// ȸ�� ��� ������ ��ȯ
//	cv::Mat mat_vec;
//	//cv::Rodrigues(Rotation, mat_vec);
//	//double radian = cv::norm(mat_vec);
//	//double degree = radian * 180.0 / CV_PI;
//
//	//std::cout << degree << "\n";
//	*/
//	return 0;
//}