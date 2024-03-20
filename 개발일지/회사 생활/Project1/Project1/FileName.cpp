// std
#include <filesystem>
#include <iostream>
#include <span>

// Exiv2
#include <exiv2/exiv2.hpp>

// Proj
#include <proj.h>

// OpenCV
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "websocket_client.h"

#pragma region 위/경도 좌표를 EPSG:5186으로 변환 -> Proj 사용

/** transform
* @brief		- proj 라이브러리(9.x.x 버전 이상)을 사용하여 메타데이터의 위/경도 좌표를 EPSG:5186으로 변환한다.
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

/** readMetadata
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
	for (const auto& exif : exifData)
	{
		if (exif.tagName() == "GPSLatitude" || exif.tagName() == "GPSLongitude")
		{
			const Exiv2::Value& value = exif.value();
			cur_value[num] = convert_gps_lon_lat(value);
			std::cout << std::format("{} = {}\n", exif.tagName(), cur_value[num]);
			num++;
			continue;
		}
		if (exif.tagName() == "GPSAltitude")
		{
			const Exiv2::Value& value = exif.value();
			cur_value[num] = convert_gps_alt(value);
			std::cout << std::format("{} = {}\n", exif.tagName(), cur_value[num]);
		}
	}

	return cur_value;
}

#pragma endregion

#pragma region 영상좌표 사진좌표로 변환 -> Exiv2 사용

/** change_video_to_img
* @brief		- 영상좌표 이미지좌표로 전환
* @param	- my_client 소켓, img_path 이미지 경로
* @return	- photo_points 이미지 좌표
*/
cv::Mat_<double> change_video_to_img(const Websocket_client& my_client, const std::string& img_path)
{
	assert(std::filesystem::exists(img_path));

	const std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open(img_path);

	const double& img_width = image->pixelWidth();
	const double& img_height = image->pixelHeight();

	/*원 영상좌표 출력
		 카메라 스펙 9248 x 6944 pixels  0.7 마이크로미터 피치(0.0000007 미터)
		 4608 x 3456 사진 = 2,304 ~ -2,304 x 1,728 ~ -1,728
	*/
	constexpr double focal_length = 4.8;
	constexpr double pixel_size = 0.0007;
	constexpr double focal_length_in_pixel = focal_length / pixel_size;

	const cv::Mat vision_to_photo = (cv::Mat_<double>(3, 3) <<
		1.0, 0.0, -(img_width / 2),
		0.0, -1.0, (img_height / 2),
		0.0, 0.0, -focal_length_in_pixel);

	std::vector<double> point_x, point_y, point_z;

	for (const auto& point : my_client._poly_vec)
	{
		const cv::Mat pos = (cv::Mat_<double>(3, 1) << point.x, point.y, 1.0);

		const cv::Mat Photo_point = vision_to_photo * pos;

		//기존 행과 열을 바꾸기위한 vec
		point_x.push_back(Photo_point.at<double>(0, 0));
		point_y.push_back(Photo_point.at<double>(1, 0));
		point_z.push_back(Photo_point.at<double>(2, 0));
	}

	const int n = static_cast<int>(point_x.size());
	cv::Mat_<double> photo_points(3, n);
	for (int i = 0; i < n; ++i)
	{
		photo_points(0, i) = point_x[i];
		photo_points(1, i) = point_y[i];
		photo_points(2, i) = point_z[i];
	}

	std::cout << "Polygon -> Changed to img!!" << '\n';
	return photo_points;
}

#pragma endregion

#pragma region 람다 구하기

/** make_lambda
* @brief		- 람다를 구함
* @param	- img_meta 이미지 메타, img_pos 이미지 좌표 
* @return	- lambda 람다
*/
double make_lambda(const cv::Mat1d& img_meta, const cv::Mat1d& img_pos)
{
	assert(not img_meta.empty() and not img_pos.empty());

	constexpr double Altitude = 20;
	return img_pos.at<double>(2, 0) / (Altitude - img_meta.at<double>(2, 0));
}
#pragma endregion

#pragma region 카메라 자세를 행렬로 구함 -> opencv 사용

/** make_rotation_matrix
* @brief		- 카메라 자세용 회전행렬을 구함
* @param	- roll x, pitch y, yaw z (double)
* @return	- Rx * Ry * Rz = R
*/
cv::Mat make_rotation_matrix(double roll, double pitch, double yaw)
{
	// 라디안으로 변환
	roll = roll * CV_PI / 180.0;
	pitch = pitch * CV_PI / 180.0;
	yaw = yaw * CV_PI / 180.0;

	// roll
	const cv::Mat Rx = (cv::Mat_<double>(3, 3) <<
		1, 0, 0,
		0, cos(roll), -sin(roll),
		0, sin(roll), cos(roll));

	// pitch
	const cv::Mat Ry = (cv::Mat_<double>(3, 3) <<
		cos(pitch), 0, sin(pitch),
		0, 1, 0,
		-sin(pitch), 0, cos(pitch));

	// yaw
	const cv::Mat Rz = (cv::Mat_<double>(3, 3) <<
		cos(yaw), -sin(yaw), 0,
		sin(yaw), cos(yaw), 0,
		0, 0, 1);

	const cv::Mat R = Ry * Rx * Rz; //z가 먼저

	return R;
}

#pragma endregion

int main()
{
	//웹 소켓 연결
	Websocket_client my_client("ws://175.116.181.24:9003");
	my_client.get_polygon();

	//사진파일 가져오기
	const std::filesystem::path cur_path = std::filesystem::current_path();
	const std::filesystem::path img_path = cur_path / "image" / "IMG_03_0000000003_L.jpg";

	//메타데이터 읽기
	std::array<double, 3> meta_data = read_meta_data(img_path.string());
	const std::array<double, 3> img_meta = transform(meta_data);
	const cv::Mat_<double> ground_meta = (cv::Mat_<double>(3, 1) << img_meta[0], img_meta[1], img_meta[2]);

	//영상좌표 -> 사진좌표
	const cv::Mat_<double> img_pos = change_video_to_img(my_client, img_path.string());

	//사진측량용 람다 구함
	const double lambda = make_lambda(ground_meta, img_pos);

	//카메라 위치
	constexpr double rotation_x = 1.0;
	constexpr double rotation_y = -1.0;
	constexpr double rotation_z = 270.0;
	const cv::Mat cam_rotation = make_rotation_matrix(rotation_x, rotation_y, rotation_z);
	cam_rotation.t();

	//실 좌표
	const cv::Mat photo = img_pos / lambda;
	const cv::Mat real_pos = cam_rotation * photo.clone();
	for (int i = 0; i < photo.cols; ++i)
	{
		real_pos.col(i) += ground_meta;
		std::cout << "real_pos [" << i << "] =\n" << real_pos.col(i) << '\n';
	}

	//exe 실행 시 바로 꺼지는거 방지용
	std::cout << '\n' << "아무키나 입력해서 종료";
	std::string test_end;
	std::cin >> test_end;

	return 0;
}
