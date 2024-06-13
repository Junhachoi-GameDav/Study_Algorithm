#pragma once
#define NOMINMAX

// std
#include <map>
#include <string>
#include <vector>
#include <mutex>
#include <array>
#include <cmath>
#include <string>
#include <locale>
#include <chrono>
#include <system_error>
//
#include <fmt/core.h>

// oneTBB
#include <oneapi/tbb/concurrent_map.h>
#include <oneapi/tbb/task_group.h>

#include "dem.h"

#include <pqxx/pqxx>
//#include <pqxx/params>


struct area
{
	cv::Point2d min;
	cv::Point2d max;

	area() = delete;

	area(const cv::Point2d& m, const cv::Point2d& M) : min(m), max(M) {}

	area(const area&) = default;
	area& operator=(const area&) = default;

	area(area&&) = default;
	area& operator=(area&&) = default;

	bool operator==(const area& other) const noexcept
	{
		return min == other.min and max == other.max;
	}
	bool operator<(const area& other) const noexcept
	{
		constexpr double epsg5186_max_x = 913114.23;
		return epsg5186_max_x * min.y + min.x < epsg5186_max_x * other.min.y + other.min.x;
	}
	bool contains(const double& x, const double& y) const noexcept
	{
		if (std::isnan(x) or std::isnan(y) or std::isinf(x) or std::isinf(y))
			return false;

		if (x < min.x or max.x < x or y < min.y or max.y < y)
			return false;

		return true;
	};
};

class dem_manager
{
	dem_manager();
	~dem_manager();
	struct dem_row
	{
		unsigned short idx;
		area boundary = { cv::Point2d{ 0, 0 }, cv::Point2d{ 0, 0 } };
		std::filesystem::path dem_path;
	};

private:
	mutable pqxx::connection con;
	mutable tbb::concurrent_map<area, demv2> dems;
	std::map<area, demv2> dems_std;
	tbb::task_group tg;

private:
	void update_progress_percentage(std::atomic<int>& progress, int total_tasks);
	void initialize(pqxx::work& wk);
	bool is_useless_dem(const demv2& dem_obj) const;
	bool is_complete_dem(const demv2& dem_obj) const;
	std::map<std::string, size_t> diagnose_dem(const demv2& dem_obj) const;

private:
	std::vector<dem_row> select_query(std::string where_clause = "true") const;
	void insert_query(const dem_row& target) const;

private:
	tbb::concurrent_map<area, demv2> preload_dem_cache;
	std::chrono::time_point<std::chrono::system_clock> end_time;
	/*
	//Thread보다 task를 이용할것
	//std::condition_variable cv; //Spurious wakeup 현상과 lost wakeup 현상이 일어날 수 있다고 한다.
	//참고 :https://a-researcher.tistory.com/30
	*/
	std::mutex mutex;
	std::atomic<bool> is_running;
	std::atomic<bool> stop_requested;
	const int hour = 5;
	void delete_map();

private:
	//DB
	const std::string table_name = "testt"; //"dem_table"

public:
	void clean_up_expired_time();
	double find_ground_height(const double& x, const double& y);
	
	static dem_manager& instance()
	{
		static dem_manager instance;
		return instance;
	}
};