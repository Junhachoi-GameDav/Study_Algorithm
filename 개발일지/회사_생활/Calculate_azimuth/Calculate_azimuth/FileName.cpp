// std
#include <iostream>
#include <filesystem>
#include <span>
#include <regex>
#include <format>

// opencv
#include <opencv2/opencv.hpp>

// Exiv2
#include <exiv2/exiv2.hpp>

// proj4
#include <proj.h>

// oneTBB
#include <oneapi/tbb/parallel_for.h>
#include <oneapi/tbb/parallel_for_each.h>
#include <oneapi/tbb/concurrent_vector.h>
#include <oneapi/tbb/task_group.h>

// pcl
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/visualization/pcl_visualizer.h>

#pragma region 위/경도 좌표를 EPSG:5186으로 변환 -> Proj 사용

/** transform
* @brief	- proj 라이브러리(9.x.x 버전 이상)을 사용하여 메타데이터의 위/경도 좌표를 EPSG:5186으로 변환한다.
* @param	- 메타데이터 std::span<double>
* @return	- 경도, 위도, 고도
*/
std::array<double, 3> transform(const std::span<double>& s)
{
	assert(s.size() <= 3);

	std::unique_ptr<PJ_CONTEXT, decltype((void(*)(PJ_CONTEXT*))(proj_context_destroy))> ctx(proj_context_create(), (void(*)(PJ_CONTEXT*))(proj_context_destroy));
	std::shared_ptr<PJ> trans_obj
	(
		proj_create_crs_to_crs
		(
			ctx.get(),
			"+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs",
			"+proj=tmerc +lat_0=38 +lon_0=127 +k=1 +x_0=200000 +y_0=600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs",
			nullptr
		),
		proj_destroy
	);
	// from src to dst
	PJ_COORD from = proj_coord(s[1], s[0], s[2], 0.0); //경도, 위도, 고도
	PJ_COORD to = proj_trans(trans_obj.get(), PJ_DIRECTION::PJ_FWD, from);

	return { to.xyz.x, to.xyz.y, to.xyz.z };
}

#pragma endregion

#pragma region 메타데이터 받고 변환 -> Exiv2 사용

/** convert_rational_to_decimal
* @brief	- 분수로 소수점 전환
* @param	- rational 경도 or 위도
*/
double convert_rational_to_decimal(const Exiv2::Rational& rational)
{
	if (rational.second == 0)
		return 0.0;
	return static_cast<double>(rational.first) / static_cast<double>(rational.second);
}

/** convert_gps_lon_lat
* @brief	- 경도, 위도 십진수로 전환
* @param	- value 경도 or 위도 메타데이터
*/
double convert_gps_lon_lat(const Exiv2::Value& value)
{
	const double degrees = convert_rational_to_decimal(value.toRational(0));
	const double minutes = convert_rational_to_decimal(value.toRational(1));
	const double seconds = convert_rational_to_decimal(value.toRational(2));

	return degrees + minutes / 60.0 + seconds / 3600.0;
}

/** convert_gps_alt
* @brief	- 고도 double로 변환
* @param	- value 고도
*/
double convert_gps_alt(const Exiv2::Value& value)
{
	const double altitude = convert_rational_to_decimal(value.toRational(0));

	return altitude;
}

/** read_meta_data
* @brief		- 이미지 경로를 받아 메타데이터를 읽어온 후 변환한다.
* @param	- img_path 이미지 경로
* @return	- cur_value 위도, 경도, 고도
*/
std::array<double, 3> read_meta_data(const std::string& img_path)
{
	assert(std::filesystem::exists(img_path));

	const std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open(img_path);

	image->readMetadata();

	const Exiv2::ExifData& exifData = image->exifData();

	std::array<double, 3> cur_value{};
	int num = 0;
	for (const auto& data : exifData)
	{
		if (data.tagName() == "GPSLatitude" || data.tagName() == "GPSLongitude")
		{
			const Exiv2::Value& value = data.value();
			cur_value[num] = convert_gps_lon_lat(value);
			std::cout << std::format("{} = {}\n", data.tagName(), cur_value[num]);
			num++;
			continue;
		}
		if (data.tagName() == "GPSAltitude")
		{
			const Exiv2::Value& value = data.value();
			cur_value[num] = convert_gps_alt(value);
			std::cout << std::format("{} = {}\n", data.tagName(), cur_value[num]);
		}
	}

	return cur_value;
}

#pragma endregion

#pragma region 영상좌표 사진좌표로 변환 -> opencv 사용

/** change_video_to_img
* @brief		- 영상좌표 이미지좌표로 전환
* @brief		- 카메라 스펙 9248 x 6944 pixels  0.7 마이크로미터 피치(0.0000007 미터), (4608 x 3456 사진 = 2,304 ~ -2,304 x 1,728 ~ -1,728)
* @param	- my_client 소켓, img_path 이미지 경로
* @return	- photo_points 이미지 좌표
*/
cv::Mat_<double> change_video_to_img(const cv::Mat& image)
{
	const int img_width = image.cols;
	const int img_height = image.rows;

	constexpr double focal_length = 4.8;
	constexpr double pixel_size = 0.0007;
	constexpr double focal_length_in_pixel = focal_length / pixel_size;

	const cv::Mat vision_to_photo = (cv::Mat_<double>(3, 3) <<
		1.0, 0.0, -(img_width / 2),
		0.0, -1.0, (img_height / 2),
		0.0, 0.0, -focal_length_in_pixel);

	cv::Mat_<double> photo_points(3, 1);

	const cv::Mat pos = (cv::Mat_<double>(3, 1) << img_width / 2, img_height / 2, 1.0);

	photo_points = vision_to_photo * pos;
	
	return photo_points;
}

#pragma endregion

#pragma region 방위각 계산
/** calculate_azimuth
* @brief		- 방위각( A to B )를 구한다.
* @param	- Ax, Ay, Bx, By
* @return	- azimuth
*/
double calculate_azimuth(double x1, double y1, double x2, double y2)
{
	const double PI = 3.14159265358979323846;

	double deltaX = x2 - x1;
	double deltaY = y2 - y1;
	double azimuth = atan2(deltaY, deltaX);
	azimuth = azimuth * (180 / PI);
	azimuth = 90 - azimuth; // 북을  0도로

	if (azimuth < 0)
		azimuth += 360.0;

	return azimuth;
}

#pragma endregion

#pragma region 회전값 변환-> opencv 사용

/** make_rotation_matrix
* @brief		- 회전행렬 변환
* @param	- 3대3 행렬 baseRotation, enum Rot_case
* @return	- Rx * Ry * Rz = R 순서 바꾸는것으로 결과값 다름
*/
enum class Rot_case
{
	XYZ,
	YXZ,
	YZX,
	ZYX,
	XZY,
	ZXY,
	END
};
cv::Mat make_rotation_matrix(cv::Mat& baseRotation, Rot_case& rot_case)
{
	// 라디안으로 변환
	double pitch = -asin(baseRotation.at<double>(2, 0));
	double roll = atan2(baseRotation.at<double>(2, 1), baseRotation.at<double>(2, 2));
	double yaw = atan2(baseRotation.at<double>(1, 0), baseRotation.at<double>(0, 0));

	// 각 축에 대한 회전 행렬 생성
	const cv::Mat Rx = (cv::Mat_<double>(3, 3) <<
		1, 0, 0,
		0, cos(roll), -sin(roll),
		0, sin(roll), cos(roll));

	const cv::Mat Ry = (cv::Mat_<double>(3, 3) <<
		cos(pitch), 0, sin(pitch),
		0, 1, 0,
		-sin(pitch), 0, cos(pitch));

	const cv::Mat Rz = (cv::Mat_<double>(3, 3) <<
		cos(yaw), -sin(yaw), 0,
		sin(yaw), cos(yaw), 0,
		0, 0, 1);

	cv::Mat R;
	switch (rot_case) {
	case Rot_case::XYZ:
		std::cout << "XYZ rotation" << '\n';
		R = Rx * Ry * Rz;
		break;
	case Rot_case::YXZ:
		std::cout << "YXZ rotation" << '\n';
		R = Ry * Rx * Rz;
		break;
	case Rot_case::YZX:
		std::cout << "YZX rotation" << '\n';
		R = Ry * Rz * Rx;
		break;
	case Rot_case::ZYX:
		std::cout << "ZYX rotation" << '\n';
		R = Rz * Ry * Rx;
		break;
	case Rot_case::XZY:
		std::cout << "XZY rotation" << '\n';
		R = Rx * Rz * Ry;
		break;
	case Rot_case::ZXY:
		std::cout << "ZXY rotation" << '\n';
		R = Rz * Rx * Ry;
		break;
	}
	return R;
}

/** make_Euler_angles
* @brief		- 회전행렬(각도) 변환
* @param	- 변환된 R행렬
* @return	- roll x, pitch y, yaw z (double)
*/
std::tuple<double, double, double> make_Euler_angles(cv::Mat& R)
{
	double pitch = -asin(R.at<double>(2, 0));
	double roll = atan2(R.at<double>(2, 1), R.at<double>(2, 2));
	double yaw = atan2(R.at<double>(1, 0), R.at<double>(0, 0));

	double roll_degrees = roll * 180.0 / CV_PI;
	double pitch_degrees = pitch * 180.0 / CV_PI;
	double yaw_degrees = yaw * 180.0 / CV_PI;

	return { roll_degrees, pitch_degrees, yaw_degrees };
}

#pragma endregion

int main()
{
	/** 번들 조정 앞단 (수정해야할 사항)
	* 프로젝션 p = k * rt, 이것을 반복적으로 구할때 기준점(idx = 0)을 두고 구해야함 즉 이미지_0 -> 이미지_1 .... 이미지_0 -> 이미지 62 이런식으로 만들어야함
	* 그러나 현재 코드는 이미지_0 -> 이미지_1 .... 이미지_61 -> 이미지62 이렇게 되어있으니 수정할 것
	* 그후에 번들 조정 (오차 최적화 기법) 할 것
	*/

	namespace fs = ::std::filesystem;

	const std::filesystem::path cur_path = std::filesystem::current_path();
	//const std::filesystem::path img_path = cur_path / "Image20231207-061900" / "IMG_03_0000000005_L.jpg";

	cv::Ptr<cv::ORB> detector = cv::ORB::create(10000);

	tbb::concurrent_vector<std::tuple<size_t, cv::Mat, std::vector<cv::KeyPoint>, cv::Mat>> image_paths;
	std::regex re("_(\\d+)_L\\.jpg$");

	tbb::parallel_for_each(fs::directory_iterator(cur_path / "Image20231207-061900"), fs::directory_iterator({}),
		[&image_paths, &re, &detector](const fs::path& path)->void
		{
			if (path.extension() != ".jpg")
				return;

			std::smatch match;
			const std::string filename = path.filename().generic_string();
			if (!std::regex_search(filename, match, re))
				return;

			cv::Mat image = cv::imread(path.generic_string());
			std::vector<cv::KeyPoint> keypoint;
			cv::Mat des;
			detector->detectAndCompute(image, cv::noArray(), keypoint, des);
			image_paths.emplace_back(std::forward_as_tuple(std::stoull(match[1].str()), image, keypoint, des));

			if (keypoint.empty())
				return;
		});

	std::sort(image_paths.begin(), image_paths.end(), [](const decltype(image_paths)::const_reference lhs, const decltype(image_paths)::const_reference rhs)->bool
		{
			const auto& [index_lhs, image_lhs, kp_lhs, des_lhs] = lhs;
			const auto& [index_rhs, image_rhs, kp_rhs, des_rhs] = rhs;

			return index_lhs < index_rhs;
		});

	//cv::Ptr<cv::ORB> detector = cv::ORB::create(2000);
	//tbb::concurrent_vector<std::vector<cv::DMatch>> matched_results(image_paths.size() - 1);
	tbb::concurrent_vector<std::tuple<size_t, cv::Mat, cv::Mat, cv::Mat>> Rot_Tran_Proj;
	//tbb::concurrent_vector<pcl::PointCloud<pcl::PointXYZ>> clouds;
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
	tbb::parallel_for(0ULL, image_paths.size() - 1ULL, [&image_paths, &detector, &Rot_Tran_Proj, &cloud](size_t i)->void
		{
			const auto& [index_0, image_0, keypoint_0, des_0] = image_paths[i];
			const auto& [index_1, image_1, keypoint_1, des_1] = image_paths[i + 1];

			cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING, true);

			std::vector<cv::DMatch> matched;
			matcher->match(des_1, des_0, matched);
			//matcher->match(des_current, des_current, matched);

			// Essential
			std::vector<cv::Point2f> points1, points2;
			for (auto& match : matched) {
				points1.push_back(keypoint_0[match.trainIdx].pt);
				points2.push_back(keypoint_1[match.queryIdx].pt);
			}

			cv::Mat mask;
			constexpr double focal = 4.8;
			cv::Point2f img_center(image_0.cols / 2, image_0.rows / 2);
			cv::Mat Essential_result = cv::findEssentialMat(points2, points1, focal, img_center, cv::RANSAC, 0.999, 1.0, mask);

			cv::Mat K = (cv::Mat_<double>(3, 3) <<
				focal, 0.0, 0.0,
				0.0, focal, 0.0,
				0.0, 0.0, 1.0);

			cv::Mat def_projection = (cv::Mat_<double>(3, 4) <<
				1.0, 0.0, 0.0, 0.0,
				0.0, 1.0, 0.0, 0.0,
				0.0, 0.0, 1.0, 0.0);

			cv::Mat def_projMat = K * def_projection;
			//std::vector<cv::Point2f> def_points;

			// 회전값(행렬)
			cv::Mat Rotation;
			cv::Mat Translation;

			cv::recoverPose(Essential_result, points2, points1, Rotation, Translation, focal, img_center, mask);

			cv::Mat Rt;
			cv::hconcat(Rotation, Translation, Rt); // 회전 행렬과 이동 벡터를 수평으로 연결

			// 투영 행렬(Projective Matrix) 
			cv::Mat Projection = K * Rt;

			// 3차원 변환
			cv::Mat points_4d;
			cv::triangulatePoints(Projection, def_projMat, points2, points1, points_4d);

			cv::Mat points_3d;
			cv::convertPointsFromHomogeneous(points_4d.t(), points_3d);

			pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
			for (int i = 0; i < points_3d.rows; i++)
			{
				pcl::PointXYZRGB point;
				point.x = points_3d.at<float>(i, 0);
				point.y = points_3d.at<float>(i, 1);
				point.z = points_3d.at<float>(i, 2);
				point.r = 255;
				point.g = 255;
				point.b = 255;

				cloud->points.push_back(point);
			}

			//pcl::visualization::PCLVisualizer viewer("3D Viewer");
			//viewer.setBackgroundColor(0, 0, 0);
			//viewer.addPointCloud<pcl::PointXYZRGB>(cloud, "sample cloud");
			//viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");
			//viewer.addCoordinateSystem(1.0);
			//viewer.initCameraParameters();
			
			//while (!viewer.wasStopped())
			//{
			//	viewer.spinOnce(100);
			//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//}

			const std::filesystem::path PCD_save_path = std::filesystem::current_path() / "Image20231207-061900" / std::format("pointcloud_{}.ply", i);
			//pcl::io::savePCDFileBinary(PCD_save_path.string(), *cloud);
			//pcl::io::savePCDFile(PCD_save_path.string(), *cloud);
			pcl::PLYWriter writer;
			writer.write(PCD_save_path.string(), *cloud);
			//pcl::io::savePCDFileASCII(PCD_save_path.string(), *cloud);
			decltype(matched) matched_filtered;
			for (int i = 0; i < mask.rows; ++i)
			{
				if (mask.data[i] == 0)
					continue;

				matched_filtered.emplace_back(matched[i]);
			}

			cv::Mat result;
			cv::drawMatches(image_1, keypoint_1, image_0, keypoint_0, matched_filtered, result);
			//cv::drawMatches(image_current, keypoint_current, image_current, keypoint_current, matched_filtered, result);
			cv::resize(result, result, result.size() / 4);
			cv::imshow("matched result", result);
			cv::waitKey(0);
			//
			Rot_Tran_Proj.push_back({ i, Rotation, Translation, Projection });

			std::cout << std::format("#{}\n {} -> {} = \n", i, i, i + 1) << Rotation << "\n";
			//std::cout << Translation << '\n';
			//std::cout << Projection << '\n';
		});

	std::sort(Rot_Tran_Proj.begin(), Rot_Tran_Proj.end(), [](const std::tuple<size_t, cv::Mat, cv::Mat, cv::Mat>& a, const std::tuple<size_t, cv::Mat, cv::Mat, cv::Mat>& b)
		{
			return std::get<0>(a) < std::get<0>(b);
		});
	std::vector<std::tuple<size_t, cv::Mat, cv::Mat, cv::Mat>> Rot_Tran_Proj_result(Rot_Tran_Proj.begin(), Rot_Tran_Proj.end());

	/*pcl::visualization::PCLVisualizer viewer("3D Viewer");
	viewer.setBackgroundColor(0, 0, 0);
	viewer.addPointCloud<pcl::PointXYZ>(clouds[0], "sample cloud");
	viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "sample cloud");

	while (!viewer.wasStopped())
	{
		viewer.spinOnce(100);
	}*/

	cv::Mat baseRotation = cv::Mat::eye(3, 3, CV_64F);
	std::vector<cv::Mat> images;
	for (auto& rot_tran_proj : Rot_Tran_Proj_result)
	{
		baseRotation = baseRotation * std::get<1>(rot_tran_proj);
		cv::Mat cur_img = std::get<1>(image_paths.at(std::get<0>(rot_tran_proj)));

		std::cout << '\n' << "----------------------------------" << '\n';
		std::cout << "#R" << std::get<0>(rot_tran_proj) + 1 << '\n' << baseRotation << "'\n\n";
		//auto test = make_rotation_matrix(baseRotation, Rot_case::YXZ);
		auto rot_idx = static_cast<Rot_case>(0); //yxz;
		auto rot_matrix = make_rotation_matrix(baseRotation, rot_idx);
		auto [roll, pitch, yaw] = make_Euler_angles(rot_matrix);
		std::cout << std::format("roll : {:.8f}\npitch : {:.8f}\nyaw : {:.8f}\n", roll, pitch, yaw);

		const int img_width = cur_img.cols;
		const int img_height = cur_img.rows;

		// 모서리
		cv::Mat corners = (cv::Mat_<double>(3, 4) <<
			0.0, img_width, 0.0, img_width,
			0.0, 0.0, img_height, img_height,
			1.0, 1.0, 1.0, 1.0);

		constexpr double focal_length = 4.8;
		constexpr double pixel_size = 0.0007;
		constexpr double focal_length_in_pixel = focal_length / pixel_size;

		const cv::Mat vision_to_photo = (cv::Mat_<double>(3, 3) <<
			1.0, 0.0, -(img_width / 2),
			0.0, -1.0, (img_height / 2),
			0.0, 0.0, -focal_length_in_pixel);

		const cv::Mat rot_photo_corners = baseRotation * vision_to_photo * corners;

		rot_photo_corners.row(2) /= -focal_length_in_pixel;
		for (int i = 0; i < 4; ++i)
			rot_photo_corners.col(i) /= static_cast<double* const>(static_cast<void* const>(rot_photo_corners.data))[i + 8];

		rot_photo_corners.row(1) = -rot_photo_corners.row(1);

		// 음수를 양수로 전환
		cv::Point2d minmax_x;
		cv::Point2d minmax_y;
		cv::minMaxIdx(rot_photo_corners.row(0), &minmax_x.x, &minmax_x.y);
		rot_photo_corners.row(0) -= minmax_x.x;
		cv::minMaxIdx(rot_photo_corners.row(1), &minmax_y.x, &minmax_y.y);
		rot_photo_corners.row(1) -= minmax_y.x;

		// 호모그래피로 투시 변환
		cv::Mat homography = cv::findHomography(corners.t(), rot_photo_corners.t(), cv::noArray(), cv::RANSAC, 0.0);
		cv::Size warped_size(static_cast<int>(std::floor(minmax_x.y - minmax_x.x)), static_cast<int>(std::floor(minmax_y.y - minmax_y.x)));

		// 이미지 출력
		cv::Mat next_img;
		cv::warpPerspective(cur_img, next_img, homography, warped_size);
		images.push_back(next_img);
		//std::get<1>(image_paths.at(0)).release();

		/*for (int i = static_cast<int>(Rot_case::XYZ); i < static_cast<int>(Rot_case::END); i++)
		{
			auto rot_idx = static_cast<Rot_case>(i);
			auto rot_matrix = make_rotation_matrix(baseRotation, rot_idx);
			auto [roll, pitch, yaw] = make_Euler_angles(rot_matrix);

			std::cout << std::format("roll : {:.8f}\npitch : {:.8f}\nyaw : {:.8f}\n", roll, pitch, yaw);
			std::cout << rot_matrix << "\n\n";
		}*/

	}
	std::cout << "test";
	return 0;
}