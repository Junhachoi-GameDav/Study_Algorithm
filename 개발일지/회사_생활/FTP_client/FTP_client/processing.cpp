#include "processing.h"

// OpenCV
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

// Boost
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/file_mapping.hpp>

// for binary file
std::vector<unsigned char> fast_file_read(const std::string& abs_path)
{
	assert(std::filesystem::exists(abs_path));
	//////////////////// add to check if the file is readable

	namespace ipc = ::boost::interprocess;

	const ipc::file_mapping file(abs_path.c_str(), ipc::read_only);
	const ipc::mapped_region region(file, ipc::read_only);

	const unsigned char* addr = static_cast<const unsigned char*>(region.get_address());
	const std::size_t size = region.get_size();
	
	return std::vector<unsigned char>(addr, addr + size);
}


// for image using OpenCV, decoding inside
cv::Mat fast_image_read(const std::string& abs_path)
{
	//////////////////// add exception handling process for imdecode() failed
	return cv::imdecode(fast_file_read(abs_path), cv::ImreadModes::IMREAD_ANYCOLOR);
}
