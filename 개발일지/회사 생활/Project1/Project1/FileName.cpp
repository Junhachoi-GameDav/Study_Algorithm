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

#pragma region ��/�浵 ��ǥ�� EPSG:5186���� ��ȯ -> Proj ���

/** transform
* @brief		- proj ���̺귯��(9.x.x ���� �̻�)�� ����Ͽ� ��Ÿ�������� ��/�浵 ��ǥ�� EPSG:5186���� ��ȯ�Ѵ�.
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

/** readMetadata
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

#pragma region ������ǥ ������ǥ�� ��ȯ -> Exiv2 ���

/** change_video_to_img
* @brief		- ������ǥ �̹�����ǥ�� ��ȯ
* @param	- my_client ����, img_path �̹��� ���
* @return	- photo_points �̹��� ��ǥ
*/
cv::Mat_<double> change_video_to_img(const Websocket_client& my_client, const std::string& img_path)
{
	assert(std::filesystem::exists(img_path));

	const std::unique_ptr<Exiv2::Image> image = Exiv2::ImageFactory::open(img_path);

	const double& img_width = image->pixelWidth();
	const double& img_height = image->pixelHeight();

	/*�� ������ǥ ���
		 ī�޶� ���� 9248 x 6944 pixels  0.7 ����ũ�ι��� ��ġ(0.0000007 ����)
		 4608 x 3456 ���� = 2,304 ~ -2,304 x 1,728 ~ -1,728
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

		//���� ��� ���� �ٲٱ����� vec
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

#pragma region ���� ���ϱ�

/** make_lambda
* @brief		- ���ٸ� ����
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
	// �������� ��ȯ
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

	const cv::Mat R = Ry * Rx * Rz; //z�� ����

	return R;
}

#pragma endregion

int main()
{
	//�� ���� ����
	Websocket_client my_client("ws://175.116.181.24:9003");
	my_client.get_polygon();

	//�������� ��������
	const std::filesystem::path cur_path = std::filesystem::current_path();
	const std::filesystem::path img_path = cur_path / "image" / "IMG_03_0000000003_L.jpg";

	//��Ÿ������ �б�
	std::array<double, 3> meta_data = read_meta_data(img_path.string());
	const std::array<double, 3> img_meta = transform(meta_data);
	const cv::Mat_<double> ground_meta = (cv::Mat_<double>(3, 1) << img_meta[0], img_meta[1], img_meta[2]);

	//������ǥ -> ������ǥ
	const cv::Mat_<double> img_pos = change_video_to_img(my_client, img_path.string());

	//���������� ���� ����
	const double lambda = make_lambda(ground_meta, img_pos);

	//ī�޶� ��ġ
	constexpr double rotation_x = 1.0;
	constexpr double rotation_y = -1.0;
	constexpr double rotation_z = 270.0;
	const cv::Mat cam_rotation = make_rotation_matrix(rotation_x, rotation_y, rotation_z);
	cam_rotation.t();

	//�� ��ǥ
	const cv::Mat photo = img_pos / lambda;
	const cv::Mat real_pos = cam_rotation * photo.clone();
	for (int i = 0; i < photo.cols; ++i)
	{
		real_pos.col(i) += ground_meta;
		std::cout << "real_pos [" << i << "] =\n" << real_pos.col(i) << '\n';
	}

	//exe ���� �� �ٷ� �����°� ������
	std::cout << '\n' << "�ƹ�Ű�� �Է��ؼ� ����";
	std::string test_end;
	std::cin >> test_end;

	return 0;
}
