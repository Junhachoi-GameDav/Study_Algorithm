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

#pragma region ��/�浵 ��ǥ�� EPSG:5186���� ��ȯ -> Proj ���

/** transform
* @brief	- proj ���̺귯��(9.x.x ���� �̻�)�� ����Ͽ� ��Ÿ�������� ��/�浵 ��ǥ�� EPSG:5186���� ��ȯ�Ѵ�.
* @param	- ��Ÿ������ std::span<double>
* @return	- �浵, ����, ��
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
	PJ_COORD from = proj_coord(s[1], s[0], s[2], 0.0); //�浵, ����, ��
	PJ_COORD to = proj_trans(trans_obj.get(), PJ_DIRECTION::PJ_FWD, from);

	return { to.xyz.x, to.xyz.y, to.xyz.z };
}

#pragma endregion

#pragma region ��Ÿ������ �ް� ��ȯ -> Exiv2 ���

/** convert_rational_to_decimal
* @brief	- �м��� �Ҽ��� ��ȯ
* @param	- rational �浵 or ����
*/
double convert_rational_to_decimal(const Exiv2::Rational& rational)
{
	if (rational.second == 0)
		return 0.0;
	return static_cast<double>(rational.first) / static_cast<double>(rational.second);
}

/** convert_gps_lon_lat
* @brief	- �浵, ���� �������� ��ȯ
* @param	- value �浵 or ���� ��Ÿ������
*/
double convert_gps_lon_lat(const Exiv2::Value& value)
{
	const double degrees = convert_rational_to_decimal(value.toRational(0));
	const double minutes = convert_rational_to_decimal(value.toRational(1));
	const double seconds = convert_rational_to_decimal(value.toRational(2));

	return degrees + minutes / 60.0 + seconds / 3600.0;
}

/** convert_gps_alt
* @brief	- �� double�� ��ȯ
* @param	- value ��
*/
double convert_gps_alt(const Exiv2::Value& value)
{
	const double altitude = convert_rational_to_decimal(value.toRational(0));

	return altitude;
}

/** read_meta_data
* @brief		- �̹��� ��θ� �޾� ��Ÿ�����͸� �о�� �� ��ȯ�Ѵ�.
* @param	- img_path �̹��� ���
* @return	- cur_value ����, �浵, ��
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

#pragma region ������ǥ ������ǥ�� ��ȯ -> opencv ���

/** change_video_to_img
* @brief		- ������ǥ �̹�����ǥ�� ��ȯ
* @brief		- ī�޶� ���� 9248 x 6944 pixels  0.7 ����ũ�ι��� ��ġ(0.0000007 ����), (4608 x 3456 ���� = 2,304 ~ -2,304 x 1,728 ~ -1,728)
* @param	- my_client ����, img_path �̹��� ���
* @return	- photo_points �̹��� ��ǥ
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

#pragma region ������ ���
/** calculate_azimuth
* @brief		- ������( A to B )�� ���Ѵ�.
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
	azimuth = 90 - azimuth; // ����  0����

	if (azimuth < 0)
		azimuth += 360.0;

	return azimuth;
}

#pragma endregion

#pragma region ȸ���� ��ȯ-> opencv ���

/** make_rotation_matrix
* @brief		- ȸ����� ��ȯ
* @param	- 3��3 ��� baseRotation, enum Rot_case
* @return	- Rx * Ry * Rz = R ���� �ٲٴ°����� ����� �ٸ�
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
	// �������� ��ȯ
	double pitch = -asin(baseRotation.at<double>(2, 0));
	double roll = atan2(baseRotation.at<double>(2, 1), baseRotation.at<double>(2, 2));
	double yaw = atan2(baseRotation.at<double>(1, 0), baseRotation.at<double>(0, 0));

	// �� �࿡ ���� ȸ�� ��� ����
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
* @brief		- ȸ�����(����) ��ȯ
* @param	- ��ȯ�� R���
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
	namespace fs = ::std::filesystem;

	const std::filesystem::path cur_path = std::filesystem::current_path();
	//const std::filesystem::path img_path = cur_path / "Image20231207-061900" / "IMG_03_0000000005_L.jpg";
	
	cv::Ptr<cv::ORB> detector = cv::ORB::create(2000);
	
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
	tbb::concurrent_vector<std::pair<size_t, cv::Mat>> Rotations;
	tbb::parallel_for(0ULL, image_paths.size() - 1ULL, [&image_paths, &detector, &Rotations](size_t i)->void
	{
		const auto& [index_current, image_current, keypoint_current, des_current] = image_paths[i];
		const auto& [index_next, image_next, keypoint_next, des_next] = image_paths[i + 1];

		cv::Ptr<cv::BFMatcher> matcher = cv::BFMatcher::create(cv::NormTypes::NORM_HAMMING, true);

		std::vector<cv::DMatch> matched;
		matcher->match(des_current, des_next, matched);

		// Essential
		std::vector<cv::Point2f> points1, points2;
		for (auto& match : matched) {
			points1.push_back(keypoint_current[match.queryIdx].pt);
			points2.push_back(keypoint_next[match.trainIdx].pt);
		}

		cv::Mat mask;
		constexpr double focal = 4.8;
		cv::Point2f photo_mid(image_current.cols / 2, image_current.rows / 2);
		cv::Mat Essential_result = cv::findEssentialMat(points1, points2, focal, photo_mid, cv::RANSAC, 0.999, 1.0, mask);

		// ȸ����(���)
		cv::Mat Rotation;
		cv::Mat Translation;
		cv::recoverPose(Essential_result, points1, points2, Rotation, Translation, focal, photo_mid, mask);

		// ������ ȸ��
		//baseRotation = baseRotation * Rotation;
		Rotations.push_back({i, Rotation});

		std::cout << std::format("#{}\n {} -> {} = \n", i, i, i + 1) << Rotation << "\n";
	});

	std::sort(Rotations.begin(), Rotations.end(), [](const std::pair<size_t, cv::Mat>& a, const std::pair<size_t, cv::Mat>& b)
	{
		return a.first < b.first;
	});
	std::vector<std::pair<size_t, cv::Mat>> Rotation_result(Rotations.begin(), Rotations.end());
	
	cv::Mat baseRotation = cv::Mat::eye(3, 3, CV_64F);
	for (auto& rot : Rotation_result)
	{
		baseRotation = baseRotation * rot.second;
		cv::Mat cur_img = std::get<1>(image_paths.at(rot.first));

		std::cout << '\n' << "----------------------------------" << '\n';
		std::cout << "#R" << rot.first + 1 << '\n' << baseRotation << "'\n\n";
		//auto test = make_rotation_matrix(baseRotation, Rot_case::YXZ);
		auto rot_idx = static_cast<Rot_case>(0); //yxz;
		auto rot_matrix = make_rotation_matrix(baseRotation, rot_idx);
		auto [roll, pitch, yaw] = make_Euler_angles(rot_matrix);

		const int img_width = cur_img.cols;
		const int img_height = cur_img.rows;

		// �𼭸�
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
		
		// ������ ����� ��ȯ
		cv::Point2d minmax_x;
		cv::Point2d minmax_y;
		cv::minMaxIdx(rot_photo_corners.row(0), &minmax_x.x, &minmax_x.y);
		rot_photo_corners.row(0) -= minmax_x.x;
		cv::minMaxIdx(rot_photo_corners.row(1), &minmax_y.x, &minmax_y.y);
		rot_photo_corners.row(1) -= minmax_y.x;

		// ȣ��׷��Ƿ� ���� ��ȯ
		cv::Mat homography = cv::findHomography(corners.t(), rot_photo_corners.t(), cv::noArray(), cv::RANSAC, 0.0);
		cv::Size warped_size(static_cast<int>(std::floor(minmax_x.y - minmax_x.x)), static_cast<int>(std::floor(minmax_y.y - minmax_y.x)));

		// �̹��� ���
		cv::Mat next_img;
		cv::warpPerspective(cur_img, next_img, homography, warped_size);

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

	return 0;
}