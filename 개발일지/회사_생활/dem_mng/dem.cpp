// std
#include <execution>
#include <fstream>
#include <filesystem>
#include <functional>
#include <map>
#include <sstream>
#include <vector>
#include <array>
#include <system_error>

//std::format 대신 사용 - g++에서 오류남...
#include <fmt/core.h>

// gdal
#include <gdal.h>
#include <gdal_priv.h>

#include <cpl_string.h>

// this
#include "dem.h"

// Boost
#include <boost/system/system_error.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/file_mapping.hpp>

// for binary file
std::vector<unsigned char> fast_file_read(const std::string& abs_path)
{
	assert(std::filesystem::exists(abs_path));
	//////////////////// add to check if the file is readable

	namespace ipc = ::boost::interprocess;

	ipc::file_mapping file(abs_path.c_str(), ipc::read_only);
	ipc::mapped_region region(file, ipc::read_only);

	const unsigned char* addr = static_cast<const unsigned char*>(region.get_address());
	const std::size_t size = region.get_size();

	return std::vector<unsigned char>(addr, addr + size);
}

demv2::demv2(const std::filesystem::path& dem_file) : abs_path(dem_file)
{
	// gdal driver를 RAII처럼 사용하려고 만든 로컬 구조체
	// thread safe하지 않으므로 멀티스레드 환경에서 여러 DEM을 동시에 읽어들일 계획이라면 방식을 바꿀 것
	static struct driver_manager
	{
		driver_manager() { GDALAllRegister(); }
		~driver_manager() { GDALDestroyDriverManager(); }
	} dm;

	struct __filemap_dem_open
	{
		std::vector<unsigned char> buffer;
		CPLString virtualFilename;
		GDALDataset* dataset_ptr;
		__filemap_dem_open(const std::filesystem::path& dem_file) : buffer(fast_file_read(dem_file.generic_string()))
		{
			virtualFilename = CPLString(fmt::format("/vsimem/{}", dem_file.stem().generic_string()));
			VSIFileFromMemBuffer(virtualFilename.c_str(), buffer.data(), buffer.size(), FALSE);
			dataset_ptr = static_cast<GDALDataset*>(GDALOpen(virtualFilename.c_str(), GDALAccess::GA_ReadOnly));
		}
		~__filemap_dem_open()
		{
			if (dataset_ptr != nullptr)
				GDALClose(dataset_ptr);

			VSIUnlink(virtualFilename.c_str());
		}
		operator GDALDataset* () const noexcept { return dataset_ptr; }
		GDALDataset* operator->() const noexcept { return dataset_ptr; }
	} dataset(dem_file);

	if (dataset == nullptr)
		return;

	std::this_thread::yield();

	double geotransform[6];
	if (dataset->GetGeoTransform(geotransform) != CE_None)
		return;

	left_top = cv::Point2d(geotransform[0], geotransform[3]);
	delta = cv::Point2d(geotransform[1], geotransform[5]);

	dem_size = cv::Size{ dataset->GetRasterXSize(), dataset->GetRasterYSize() };
	if (dem_size.width <= 0 or dem_size.height <= 0)
		return;

	// 1개 채널만 있다고 가정
	// 밴드에 높이값만 들어있는게 아니면 코드 수정해야 함
	GDALRasterBand* poBand = dataset->GetRasterBand(1);

	// 밴드 접근하여 데이터 읽어오기
	dem_matrix.create(dem_size, CV_32F);
	float* const scanline = static_cast<float* const>(static_cast<void* const>(dem_matrix.data));
	if (poBand->RasterIO(GF_Read, 0, 0, dem_size.width, dem_size.height, scanline, dem_size.width, dem_size.height, GDT_Float32, 0, 0) != CE_None)
		return;
}

bool demv2::contains(const double& x, const double& y) const
{
	// check if invalid
	if (std::isnan(x) or std::isnan(y) or std::isinf(x) or std::isinf(y))
		return false;

	// check if smaller than minimum
	cv::Point2d right_bottom(left_top.x + delta.x * dem_size.width, left_top.y + delta.y * dem_size.height);
	if (x < left_top.x or right_bottom.x < x)
		return false;

	if (left_top.y < y or y < right_bottom.y)
		return false;

	return true;
}

double demv2::find_ground_height(const double& x, const double& y) const
{
	if (!contains(x, y))
		return std::nan("point is either not in the area or invalid");


	// x, y의 DEM에서의 픽셀 위치
	const cv::Point2d pixel_coord((x - left_top.x) / delta.x, (y - left_top.y) / delta.y);

	const cv::Point floors(static_cast<int>(std::floor(pixel_coord.x)), static_cast<int>(std::floor(pixel_coord.y)));
	const cv::Point ceils(static_cast<int>(std::ceil(pixel_coord.x)), static_cast<int>(std::ceil(pixel_coord.y)));

	// 높이를 찾을 때 처음 찾은 점과 그리 멀지 않은 점을 찾을 확률이 높기 때문에 이 함수가 반환된 후에도 언로드 되지 않음
	// 수동으로 내릴 것
	if (dem_matrix.empty())
		reload();

	const float adjecent_heights[4]
	{
		static_cast<float* const>(static_cast<void* const>(dem_matrix.data))[dem_size.width * floors.y + floors.x],
		static_cast<float* const>(static_cast<void* const>(dem_matrix.data))[dem_size.width * floors.y + ceils.x],
		static_cast<float* const>(static_cast<void* const>(dem_matrix.data))[dem_size.width * ceils.y + floors.x],
		static_cast<float* const>(static_cast<void* const>(dem_matrix.data))[dem_size.width * ceils.y + ceils.x]
	};
	const double weights[4]
	{
		(static_cast<double>(ceils.x) - pixel_coord.x) * (static_cast<double>(ceils.y) - pixel_coord.y),
		(pixel_coord.x - static_cast<double>(floors.x)) * (static_cast<double>(ceils.y) - pixel_coord.y),
		(static_cast<double>(ceils.x) - pixel_coord.x) * (pixel_coord.y - static_cast<double>(floors.y)),
		(pixel_coord.x - static_cast<double>(floors.x)) * (pixel_coord.y - static_cast<double>(floors.y))
	};
	// std::abs(delta.x * delta.y)*
	// std::abs(delta.x * delta.y)*
	// std::abs(delta.x * delta.y)*
	// std::abs(delta.x * delta.y)*
	return weights[0] * adjecent_heights[0] + weights[1] * adjecent_heights[1] + weights[2] * adjecent_heights[2] + weights[3] * adjecent_heights[3];
}

void demv2::unload() const
{
	if (not dem_matrix.empty())
		dem_matrix.release();
}

void demv2::reload() const
{
	if (dem_matrix.empty())
		this->dem_matrix = demv2(abs_path).dem_matrix;
}
