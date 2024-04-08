// std
#include <iostream>
#include <filesystem>
#include <span>
#include <cmath>
#include <regex>

// opencv
#include <opencv2/opencv.hpp>

// Exiv2
#include <exiv2/exiv2.hpp>

// proj4
#include <proj.h>

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


int main()
{
	const std::filesystem::path cur_path = std::filesystem::current_path();
	const std::filesystem::path img_path = cur_path / "Image20231207-061900" / "IMG_03_0000000062_L.jpg";

	std::regex re("_(\\d+)_L\\.jpg$");
	std::smatch match;

	std::string filename = img_path.filename().string();

	std::vector<std::pair<double, double>, std::pair<double, double>> real_pos_vec;

	if (std::regex_search(filename, match, re) && match.size() > 1)
	{
		std::string numStr = match.str(1);
		int numLength = numStr.length();
		for (int i = 0; i <= std::stoi(numStr); ++i)
		{
			std::stringstream ss;
			ss << std::setw(numLength) << std::setfill('0') << i;

			// 새로운 파일 이름 생성
			std::string new_filename = std::regex_replace(filename, re, "_" + ss.str() + "_L.jpg");
			std::filesystem::path new_path = img_path.parent_path() / new_filename;
			
			cv::Mat image = cv::imread(img_path.string());

			std::array<double, 3> meta_data = read_meta_data(new_path.string());
			const std::array<double, 3> img_meta = transform(meta_data);
			const cv::Mat_<double> ground_meta = (cv::Mat_<double>(3, 1) << img_meta[0], img_meta[1], img_meta[2]);

			const cv::Mat_<double> img_pos = change_video_to_img(image);

			constexpr double Altitude = 20;
			double lambda = img_pos.at<double>(2, 0) / (Altitude - ground_meta.at<double>(2, 0));

			cv::Mat real_pos = img_pos / lambda;
			real_pos += ground_meta;

			cv::Mat previous_real_pos = real_pos;
			real_pos_vec.push_back({{ real_pos.at<double>(0, 0), real_pos.at<double>(1, 0) },{ previous_real_pos.at<double>(0,0),previous_real_pos.at<double>(1,0) } });
			std::cout << "\n";
		}
	}

	for (auto it : real_pos_vec)
	{
		double test = calculate_azimuth(it.)
	}

	return 0;
}