#pragma once

// std
#include <filesystem>
#include <string>
#include <vector>

// OpenCV
#include <opencv2/core.hpp>

// for binary file
std::vector<unsigned char> fast_file_read(const std::string& abs_path);
inline std::vector<unsigned char> fast_file_read(const std::filesystem::path& abs_path)
{
	return fast_file_read(abs_path.generic_string());
}

// for image using OpenCV, decoding inside
cv::Mat fast_image_read(const std::string& abs_path);
inline cv::Mat fast_image_read(const std::filesystem::path& abs_path)
{
	return fast_image_read(abs_path.generic_string());
}