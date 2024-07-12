 //std
#include <iostream>
#include <format>

 //lib
#include <proj.h>

 
#include "coordinate_transform.hpp"
#include "build_config.h"
//
//std::string get_proj_string(PJ_CONTEXT* ctx, const char* epsg_code)
//{
//	PJ* pj = proj_create(ctx, std::format("EPSG:{}", epsg_code).c_str());
//	if (pj == nullptr)
//		return;
//
//	const std::string& proj_string = proj_as_proj_string(ctx, pj.get(), PJ_PROJ_5, nullptr);
//	std::string result = proj_string;
//	
//	proj_destroy(pj);
//	return result;
//}

int main()
{
	// √ ±‚»≠
	configuration::read_config();
	
	coordinate_transform& coord_trans = coordinate_transform::instance();

	constexpr const char* src_coord = "4326";

	constexpr const char* coords[]
	{
		"32632", "3857", "27700", "23032", 
		"26917", "31256", "32633", "2975", "32636", 
		"3413", "3035", "5514", "25832", "31467", "32721",
		"32734", "32644", "3995", "32736", "32650", 
		"25833", "3726", "32740", "20348", "31258", 
		"26191", "26712", "3006", "2263"
	};
	constexpr const char* target_coord = "5186";
	double points[3]{ 127.100953, 37.401643, 0.0 };
	
	double transformed_points[29][3]{ 0 };
	double _5186_points[3];

	/*for (int i = 0; i < 29; ++i)
	{
		transformed_points[i][0] = points[0];
		transformed_points[i][1] = points[1];
		transformed_points[i][2] = points[2];
		coord_trans.transform(src_coord, coords[i], transformed_points[i]);
		_5186_points[0] = transformed_points[i][0];
		_5186_points[1] = transformed_points[i][1];
		_5186_points[2] = transformed_points[i][2];
		coord_trans.transform(coords[i], target_coord,  _5186_points);
		std::cout << std::format("EPSG: 4326 > EPSG: {} > EPSG:5186 -> {}, {}, {}\n", coords[i], _5186_points[0], _5186_points[1], _5186_points[2]);
	}*/

	auto result = coord_trans.transform("4326", " 5186", points);
	std::cout << std::format("From EPSG: {}  to EPSG:5186 -> {}, {}, {}\n", "4326", result[0], result[1], result[2]);

	/*for (const auto& coord : coords)
	{
		double points[3]{ 0, 0, 0 };

		auto result = coord_trans.transform(coord, target_coord, points);

		std::cout << std::format("From EPSG: {}  to EPSG:5186 -> {}, {}, {}\n", coord, points[0], points[1], points[2] );

		std::cout << std::format("From EPSG: {}  to EPSG:5186 -> {}, {}, {}\n", coord, result[0], result[1], result[2]);
	}*/
	//proj_context_destroy(ctx);

	return 0;
}