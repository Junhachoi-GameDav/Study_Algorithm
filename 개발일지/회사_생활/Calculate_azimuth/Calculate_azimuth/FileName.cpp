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

			// ���ο� ���� �̸� ����
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