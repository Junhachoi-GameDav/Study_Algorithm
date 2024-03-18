#include <iostream>
#include <fstream>
#include <span>

#include "websocket_client.h"

#include <exiv2/exiv2.hpp>

#include <proj.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>


//proj ������ �޾Ƽ� ���
//-	proj ���̺귯��(9.x.x ���� �̻�)�� ����Ͽ� ��Ÿ�������� ��/�浵 ��ǥ�� EPSG:5186���� ��ȯ�Ѵ�. 
#pragma region proj ?
//double Mat_changeTo_double(const cv::Mat& mat)
//{
//	return mat.at<double>(0);
//}
//std::array<double, 3> transform(const std::vector<cv::Mat>& s)
//{
//	double longitude = Mat_changeTo_double(s[1]); // �浵
//	double latitude = Mat_changeTo_double(s[0]); // ����
//	double altitude = Mat_changeTo_double(s[2]); // ��
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
//	PJ_COORD from = proj_coord(longitude, latitude, altitude, 0.0); //�浵, ����, ��
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
	PJ_COORD from = proj_coord(s[1], s[0], s[2], 0.0); //�浵, ����, ��
	PJ_COORD to = proj_trans(trans_obj.get(), PJ_DIRECTION::PJ_FWD, from);

	return { to.xyz.x, to.xyz.y, to.xyz.z };
}

//��ȯ
double convertRationalToDecimal(const Exiv2::Rational& rational)
{
	if (rational.second == 0) return 0.0; // �и� 0�̸� ��ȯ�� �� ����
	return static_cast<double>(rational.first) / static_cast<double>(rational.second);
}

double convertGPSCoordinate(const Exiv2::Value& value)
{
	// '��-��-��' ���� �������� ��ȯ

	double degrees = convertRationalToDecimal(value.toRational(0));
	if (value.count() < 2) { return degrees; } //���� �ִٸ�

	double minutes = convertRationalToDecimal(value.toRational(1));
	if (value.count() < 3) { return degrees + minutes; } //��, �� �� �ִٸ�

	double seconds = convertRationalToDecimal(value.toRational(2));

	return degrees + minutes / 60.0 + seconds / 3600.0;
}


//��Ÿ������ �б�
std::array<double, 3> cur_value;
double img_width = 0;
double img_height = 0;

void ReadMetadata() {
	std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open("IMG_03_0000000003_L.jpg");
	if (!image) { return; }

	image->readMetadata();

	Exiv2::ExifData& exifData = image->exifData();
	if (exifData.empty()) { return; }

	//���μ��� ���
	img_width = image->pixelWidth();
	img_height = image->pixelHeight();

	int num = 0;
	for (auto& i : exifData)
	{
		//���� , �浵 , ��
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

//������ǥ �̹�����ǥ�� ��ȯ
cv::Mat_<double> cam_pos_changeTo_img_pos(const websocket_client& my_client)
{
	constexpr double focal_length = 4.8;
	constexpr double pixel_size = 0.0007;
	constexpr double focal_length_in_pixel = focal_length / pixel_size;

	cv::Mat vision_to_photo = (cv::Mat_<double>(3, 3) <<
		1.0, 0.0, -(img_width / 2),
		0.0, -1.0, (img_height / 2),
		0.0, 0.0, -focal_length_in_pixel);

	//cv::Mat_<double> photo_points;
	std::vector<double> xs, ys, zs;
	
	for (const auto& i : my_client._poly_vec)
	{
		//�� ������ǥ ���
		//std::cout << "video pos = " << i.x << ' ' << i.y << '\n';
		// ī�޶� ���� 9248 x 6944 pixels  0.7 ����ũ�ι��� ��ġ(0.0000007 ����)
		// 4608 x 3456 ���� = 2,304 ~ -2,304 x 1,728 ~ -1,728

		cv::Mat pos = (cv::Mat_<double>(3, 1) << i.x, i.y, 1.0);

		cv::Mat Photo_point = vision_to_photo * pos;

		//���� ��� ���� �ٲٱ����� vec
		xs.push_back(Photo_point.at<double>(0, 0));
		ys.push_back(Photo_point.at<double>(1, 0));
		zs.push_back(Photo_point.at<double>(2, 0));
	}

	int n = xs.size();
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

//���� ���ϱ�
constexpr double Altitude = 20;
double make_lamda(const cv::Mat1d& img_meta, const cv::Mat1d& img_pos)
{
	return img_pos.at<double>(2, 0) / (Altitude - img_meta.at<double>(2, 0));
}

//ȸ����� (ī�޶� �ڼ�)
constexpr double rx = 1.0;
constexpr double ry = -1.0;
constexpr double rz = 270.0;
cv::Mat eulerToRotationMatrix(double roll, double pitch, double yaw) {
	// �������� ��ȯ
	roll = roll * CV_PI / 180.0;
	pitch = pitch * CV_PI / 180.0;
	yaw = yaw * CV_PI / 180.0;

	// roll
	cv::Mat Rx = (cv::Mat_<double>(3, 3) << 
		1, 0, 0,
		0, cos(roll), -sin(roll),
		0, sin(roll), cos(roll));

	// pitch
	cv::Mat Ry = (cv::Mat_<double>(3, 3) <<
		cos(pitch), 0, sin(pitch),
		0, 1, 0,
		-sin(pitch), 0, cos(pitch));

	// yaw
	cv::Mat Rz = (cv::Mat_<double>(3, 3) <<
		cos(yaw), -sin(yaw), 0,
		sin(yaw), cos(yaw), 0,
		0, 0, 1);

	cv::Mat R = Ry * Rx * Rz; //z�� ����
	return R;
}

int main() {

	websocket_client my_client("ws://175.116.181.24:9003");
	
    ReadMetadata();

	auto img_meta = transform(cur_value);
	cv::Mat_<double> ground_meta = (cv::Mat_<double>(3, 1) << img_meta[0], img_meta[1], img_meta[2]);

	my_client.run();
	
	auto img_pos = cam_pos_changeTo_img_pos(my_client);

	auto lamda = make_lamda(ground_meta, img_pos);

	auto cam_rot = eulerToRotationMatrix(rx, ry, rz);
	cam_rot.t(); //��ġ ���

	//�� ��ǥ
	cv::Mat p = img_pos / lamda;
	cv::Mat real_pos = cam_rot * p.clone();
	for (int i = 0; i < p.cols; ++i)
	{
		real_pos.col(i) += ground_meta;
		std::cout << "real_pos["<< i << "] =\n" << real_pos.col(i) << '\n';
	}
	std::cout << "test";
	
	
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
