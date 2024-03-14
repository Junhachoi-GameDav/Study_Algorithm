#include <iostream>
#include <fstream>
#include <span>

#include "websocket_client.h"

#include <exiv2/exiv2.hpp>

#include <proj.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>


//proj 파일을 받아서 계산
//-	proj 라이브러리(9.x.x 버전 이상)을 사용하여 메타데이터의 위/경도 좌표를 EPSG:5186으로 변환한다. 
#pragma region proj ?
//double Mat_changeTo_double(const cv::Mat& mat)
//{
//	return mat.at<double>(0);
//}
//std::array<double, 3> transform(const std::vector<cv::Mat>& s)
//{
//	double longitude = Mat_changeTo_double(s[1]); // 경도
//	double latitude = Mat_changeTo_double(s[0]); // 위도
//	double altitude = Mat_changeTo_double(s[2]); // 고도
//
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
//	PJ_COORD from = proj_coord(longitude, latitude, altitude, 0.0); //경도, 위도, 고도
//	PJ_COORD to = proj_trans(trans_obj.get(), PJ_DIRECTION::PJ_FWD, from);
//
//	return { to.xyz.x, to.xyz.y, to.xyz.z };
//}

#pragma endregion

std::array<double, 3> transform(const std::span<double>& s)
{

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

//변환
double convertRationalToDecimal(const Exiv2::Rational& rational)
{
	if (rational.second == 0) return 0.0; // 분모가 0이면 변환할 수 없음
	return static_cast<double>(rational.first) / static_cast<double>(rational.second);
}

double convertGPSCoordinate(const Exiv2::Value& value)
{
	// '도-분-초' 값을 십진수로 변환

	double degrees = convertRationalToDecimal(value.toRational(0));
	if (value.count() < 2) { return degrees; } //도만 있다면

	double minutes = convertRationalToDecimal(value.toRational(1));
	if (value.count() < 3) { return degrees + minutes; } //도, 분 만 있다면

	double seconds = convertRationalToDecimal(value.toRational(2));

	return degrees + minutes / 60.0 + seconds / 3600.0;
}


//메타데이터 읽기
std::array<double, 3> cur_value;
double img_width = 0;
double img_height = 0;

void ReadMetadata() {
	std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open("IMG_03_0000000003_L.jpg");
	if (!image) { return; }

	image->readMetadata();

	Exiv2::ExifData& exifData = image->exifData();
	if (exifData.empty()) { return; }

	//가로세로 얻기
	img_width = image->pixelWidth();
	img_height = image->pixelHeight();

	int num = 0;
	for (auto& i : exifData)
	{
		//위도 , 경도 , 고도
		if (i.tagName() == "GPSLatitude" || i.tagName() == "GPSLongitude" || i.tagName() == "GPSAltitude")
		{
			const Exiv2::Value& value = i.value();
			std::cout << i.tagName() << " = " << i.value() << '\n';
			//std::format("{} = {}\n", i.tagName(), i.value());
			cur_value[num] = convertGPSCoordinate(value);
			std::cout << i.tagName() << " = " << cur_value[num] << '\n';
			num++;
		}
	}
}

//영상좌표 이미지좌표로 전환
cv::Mat_<double> cam_pos_changeTo_img_pos(const websocket_client& my_client)
{
	constexpr double focal_length = 4.8;
	constexpr double pixel_size = 0.0007;
	constexpr double focal_length_in_pixel = focal_length / pixel_size;

	cv::Mat vision_to_photo = (cv::Mat_<double>(3, 3) <<
		1.0, 0.0, -(img_width / 2),
		0.0, -1.0, (img_height / 2),
		0.0, 0.0, -focal_length_in_pixel);

	cv::Mat_<double> photo_points;

	for (const auto& i : my_client._poly_vec)
	{
		//원 영상좌표 출력
		//std::cout << "video pos = " << i.x << ' ' << i.y << '\n';
		// 카메라 스펙 9248 x 6944 pixels  0.7 마이크로미터 피치(0.0000007 미터)
		// 4608 x 3456 사진 = 2,304 ~ -2,304 x 1,728 ~ -1,728

		cv::Mat pos = (cv::Mat_<double>(3, 1) << i.x, i.y, 1.0);

		cv::Mat Photo_point = vision_to_photo * pos;

		photo_points.push_back(Photo_point);
	}
	std::cout << "Polygon -> Changed to img!!" << '\n';
	return photo_points;
}

//지상 좌표로 변환
//




int main() {

	websocket_client my_client("ws://175.116.181.24:9003");
	
    ReadMetadata();

	auto img_meta = transform(cur_value);


	cv::Mat_<double> ground = (cv::Mat_<double>(3, 1) << img_meta[0], img_meta[1], img_meta[2]);
	
	my_client.run();
	
	auto img_pos = cam_pos_changeTo_img_pos(my_client);


	
	
	/*
	cv::Mat point(3, 1, CV_64F);
	static_cast<double* const>(static_cast<void* const>(point.data))[0] = static_cast<double>(polygon[0].first);
	static_cast<double* const>(static_cast<void* const>(point.data))[1] = static_cast<double>(polygon[0].second);
	static_cast<double* const>(static_cast<void* const>(point.data))[2] = 1.0;

	cv::Mat transform(3, 3, CV_64F);
	cv::Mat result = 2.0 * point;
	*/
	//transform(cur_value);
	//std::stod();

	return 0;
}
