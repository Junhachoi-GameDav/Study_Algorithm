// std
#include <filesystem>
#include <iostream>
#include <span>
#include <numbers>
// Exiv2
#include <exiv2/exiv2.hpp>

// Proj
#include <proj.h>

// OpenCV
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include "websocket_client.h"

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
cv::Mat_<double> change_video_to_img(const Websocket_client& my_client, const cv::Mat& image)
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

	const int ploy_size = static_cast<int>(my_client._poly_vec.size());
	cv::Mat_<double> photo_points(3, ploy_size);

	for (int i = 0; i < my_client._poly_vec.size(); ++i)
	{
		const cv::Point& point = my_client._poly_vec[i];
	
		const cv::Mat pos = (cv::Mat_<double>(3, 1) << point.x, point.y, 1.0);
	
		photo_points.col(i) = vision_to_photo * pos;
	}

	std::cout << "Polygon -> Changed to img!!" << '\n';
	return photo_points;
}

#pragma endregion

#pragma region ���������� ����(����) ���ϱ�

/** make_lambda
* @brief		- ���������� ����(����)�� ����
* @param	- img_meta �̹��� ��Ÿ, img_pos �̹��� ��ǥ 
* @return	- lambda ����
*/
double make_lambda(const cv::Mat1d& img_meta, const cv::Mat1d& img_pos)
{
	assert(not img_meta.empty() and not img_pos.empty());

	constexpr double Altitude = 20;
	return img_pos.at<double>(2, 0) / (Altitude - img_meta.at<double>(2, 0));
}
#pragma endregion

#pragma region ī�޶� �ڼ��� ��ķ� ���� -> opencv ���

/** make_rotation_matrix
* @brief		- ī�޶� �ڼ��� ȸ������� ����
* @param	- roll x, pitch y, yaw z (double)
* @return	- Rx * Ry * Rz = R
*/
cv::Mat make_rotation_matrix(double roll, double pitch, double yaw)
{
	constexpr double pi = std::numbers::pi;

	// �������� ��ȯ
	roll = roll * pi / 180.0;
	pitch = pitch * pi / 180.0;
	yaw = yaw * pi / 180.0;

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

	const cv::Mat R = Ry * Rx * Rz; //z�� ����

	return R;
}

#pragma endregion

int main()
{
	// �� ���� ����
	Websocket_client my_client("ws://175.116.181.24:9003");
	my_client.get_polygon();

	// �������� ��������
	const std::filesystem::path cur_path = std::filesystem::current_path();
	const std::filesystem::path img_path = cur_path / "image" / "IMG_03_0000000003_L.jpg";
	assert(std::filesystem::exists(img_path));
	cv::Mat image = cv::imread(img_path.string());
	
	// ��Ÿ������ �б�
	std::array<double, 3> meta_data = read_meta_data(img_path.string());
	const std::array<double, 3> img_meta = transform(meta_data);
	const cv::Mat_<double> ground_meta = (cv::Mat_<double>(3, 1) << img_meta[0], img_meta[1], img_meta[2]);

	// ������ǥ -> ������ǥ
	const cv::Mat_<double> img_pos = change_video_to_img(my_client, image);

	// ���������� ����(����) ���ϱ�
	const double lambda = make_lambda(ground_meta, img_pos);

	// ī�޶� ��ġ
	constexpr double rotation_x = 1.0;
	constexpr double rotation_y = -1.0;
	constexpr double rotation_z = 50.0;
	const cv::Mat cam_rotation = make_rotation_matrix(rotation_x, rotation_y, rotation_z);
	cam_rotation.t();

	// ���� ��ǥ
	const cv::Mat photo = img_pos / lambda;
	const cv::Mat real_pos = cam_rotation * photo.clone();
	for (int i = 0; i < photo.cols; ++i)
	{
		real_pos.col(i) += ground_meta;
		// std::cout << '\n' << "real_pos [" << i << "] =\n" << real_pos.col(i) << '\n';
	}

#pragma region ȣ��׷���(���� ��ȯ) => ���� �𼭸� ���� �� ȸ��

	const int img_width = image.cols;
	const int img_height = image.rows;

	// ���� �𼭸� ���ϱ�
	cv::Mat corners = (cv::Mat_<double>(3, 4) <<
		0.0, img_width, 0.0, img_width,
		0.0, 0.0, img_height, img_height,
		1.0, 1.0, 1.0, 1.0);

	// vision_to_photo�� ���ϱ�
	constexpr double focal_length = 4.8;
	constexpr double pixel_size = 0.0007;
	constexpr double focal_length_in_pixel = focal_length / pixel_size;

	const cv::Mat vision_to_photo = (cv::Mat_<double>(3, 3) <<
		1.0, 0.0, -(img_width / 2),
		0.0, -1.0, (img_height / 2),
		0.0, 0.0, -focal_length_in_pixel);

	const cv::Mat rot_photo_corners = cam_rotation * vision_to_photo * corners;

	// �ٽ� ������ǥ�� ��ȯ
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
	cv::Mat copy_img;
	cv::warpPerspective(image, copy_img, homography, warped_size);

	image.release();

#pragma endregion


	// exe ���� �� �ٷ� �����°� ������
	std::cout << '\n' << "�ƹ�Ű�� �Է��ؼ� ����";
	std::string test_end;
	std::cin >> test_end;

	return 0;
}
