#include <iostream>
#include <fstream>
#include <span>
#include <filesystem>

#include "websocket_client.h"

#include <exiv2/exiv2.hpp>

#include <proj.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

//전역이 아니게 고치기 -> 최대한 전역변수는 없는게 좋다.
//전역변수에 의존하는 함수는 좋지 않다.

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

//변환
double convertRationalToDecimal(const Exiv2::Rational& rational)
{
	if (rational.second == 0) 
		return 0.0; // 분모가 0이면 변환할 수 없음

	return static_cast<double>(rational.first) / static_cast<double>(rational.second);
}

double convertGPSCoordinate(const Exiv2::Value& value) // '도-분-초' 값을 십진수로 변환
{
	const double degrees = convertRationalToDecimal(value.toRational(0));
	if (value.count() < 2) //도만 있다면
		return degrees;

	const double minutes = convertRationalToDecimal(value.toRational(1));
	if (value.count() < 3) //도, 분 만 있다면
		return degrees + minutes;

	const double seconds = convertRationalToDecimal(value.toRational(2));

	return degrees + minutes / 60.0 + seconds / 3600.0;
}

//메타데이터 읽기
std::array<double, 3> readMetadata(const std::string& img_path)
{
	assert(std::filesystem::exists(img_path));

	const std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open(img_path);
	
	image->readMetadata();

	const Exiv2::ExifData& exifData = image->exifData();
	
	std::array<double, 3> cur_value{};
	int num = 0;
	for (const auto& i : exifData)
	{
		//위도 , 경도 , 고도
		if (i.tagName() == "GPSLatitude" || i.tagName() == "GPSLongitude" || i.tagName() == "GPSAltitude")
		{
			const Exiv2::Value& value = i.value();
			cur_value[num] = convertGPSCoordinate(value);
			std::cout << std::format("{} = {}\n", i.tagName(), cur_value[num]);
			num++;
		}
	}

	return cur_value;
}

//영상좌표 이미지좌표로 전환
cv::Mat_<double> camPos_ChangeTo_ImgPos(const websocket_client& my_client, const std::string& img_path)
{
	assert(std::filesystem::exists(img_path));

	const std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open(img_path);
	
	const double& img_width = image->pixelWidth();
	const double& img_height = image->pixelHeight();

	constexpr double focal_length = 4.8;
	constexpr double pixel_size = 0.0007;
	constexpr double focal_length_in_pixel = focal_length / pixel_size;

	const cv::Mat vision_to_photo = (cv::Mat_<double>(3, 3) <<
		1.0, 0.0, -(img_width / 2),
		0.0, -1.0, (img_height / 2),
		0.0, 0.0, -focal_length_in_pixel);

	std::vector<double> xs, ys, zs;
	
	for (const auto& i : my_client._poly_vec)
	{
		//원 영상좌표 출력
		// 카메라 스펙 9248 x 6944 pixels  0.7 마이크로미터 피치(0.0000007 미터)
		// 4608 x 3456 사진 = 2,304 ~ -2,304 x 1,728 ~ -1,728

		const cv::Mat pos = (cv::Mat_<double>(3, 1) << i.x, i.y, 1.0);

		const cv::Mat Photo_point = vision_to_photo * pos;

		//기존 행과 열을 바꾸기위한 vec
		xs.push_back(Photo_point.at<double>(0, 0));
		ys.push_back(Photo_point.at<double>(1, 0));
		zs.push_back(Photo_point.at<double>(2, 0));
	}

	const int n = static_cast<int>(xs.size());
	cv::Mat_<double> photo_points(3, n); 
	for (int i = 0; i < n; ++i)
	{
		photo_points(0, i) = xs[i];
		photo_points(1, i) = ys[i];
		photo_points(2, i) = zs[i];
	}

	std::cout << "Polygon -> Changed to img!!" << '\n';
	return photo_points;
}

//람다 구하기
double makeLamda(const cv::Mat1d& img_meta, const cv::Mat1d& img_pos)
{
	assert(not img_meta.empty() and not img_pos.empty());

	constexpr double Altitude = 20;
	return img_pos.at<double>(2, 0) / (Altitude - img_meta.at<double>(2, 0));
}

//회전행렬 (카메라 자세)
cv::Mat eulerToRotationMatrix(double roll, double pitch, double yaw) {
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

int main() {
	
	//웹 소켓 연결
	websocket_client my_client("ws://175.116.181.24:9003");
	my_client.runAndGetPolygon();


	//사진파일 가져오기
	const std::filesystem::path cur_path = std::filesystem::current_path(); //현재 디렉토리 가져옴
	const std::filesystem::path img_path = cur_path / "image" / "IMG_03_0000000003_L.jpg";
	

	//메타데이터 읽기
	std::array<double, 3> meta_data = readMetadata(img_path.string());
	const std::array<double, 3> img_meta = transform(meta_data);
	const cv::Mat_<double> ground_meta = (cv::Mat_<double>(3, 1) << img_meta[0], img_meta[1], img_meta[2]);


	//영상좌표 -> 사진좌표
	const cv::Mat_<double> img_pos = camPos_ChangeTo_ImgPos(my_client, img_path.string());
	

	//람다
	const double lamda = makeLamda(ground_meta, img_pos);

	//카메라 위치
	constexpr double rotation_x = 1.0;
	constexpr double rotation_y = -1.0;
	constexpr double rotation_z = 270.0;
	const cv::Mat cam_rotation = eulerToRotationMatrix(rotation_x, rotation_y, rotation_z);
	cam_rotation.t(); //전치 행렬


	//실 좌표
	const cv::Mat photo = img_pos / lamda;
	const cv::Mat real_pos = cam_rotation * photo.clone();
	for (int i = 0; i < photo.cols; ++i)
	{
		real_pos.col(i) += ground_meta;
		std::cout << "real_pos["<< i << "] =\n" << real_pos.col(i) << '\n';
	}


	//exe 실행시 바로 꺼지는거 방지용
	std::string test_end;
	std::cin >> test_end;

	return 0;
}
