#pragma once
// std
#include <array>
#include <format>
#include <iostream>
#include <map>
#include <span>

// proj
#include <proj.h>
#include <proj/coordinates.hpp>

// oneTBB
#include <oneapi/tbb/queuing_rw_mutex.h>

#define COORDINATE_TRANSFORM_DEFINITION

#ifdef COORDINATE_TRANSFORM_DEFINITION

//enum class coordinates
//{
//	c3857, c32652, c4326, c5186, c5187, c5179, c5714
//};
//
//static constexpr coordinates default_src_coord = coordinates::c4326;
//static constexpr coordinates default_dst_coord = coordinates::c5186;
//static const std::map<coordinates, const char* const> coord_info
//{
//	{ coordinates::c3857, "+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +no_defs" },
//	{ coordinates::c4326, "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs" },
//	{ coordinates::c5186, "+proj=tmerc +lat_0=38 +lon_0=127 +k=1 +x_0=200000 +y_0=600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs" },
//	{ coordinates::c5187, "+proj=tmerc +lat_0=38 +lon_0=129 +k=1 +x_0=200000 +y_0=600000 +ellps=GRS80 +units=m +no_defs" },
//	{ coordinates::c5179, "+proj=tmerc +lat_0=38 +lon_0=127.5 +k=0.9996 +x_0=1000000 +y_0=2000000 +ellps=GRS80 +units=m +no_defs" },
//	{ coordinates::c5714, "+proj=longlat +datum=ETRS89 +no_defs" },
//	{ coordinates::c32652, "+proj=utm +zone=52 +datum=WGS84 +units=m +no_defs" }
//};

class coordinate_transform
{
	coordinate_transform();
	PJ_CONTEXT* ctx;
	std::map<std::tuple<std::string, std::string>, std::shared_ptr<PJ>> trans_objects;

	tbb::queuing_rw_mutex mtx;
public:
	~coordinate_transform();
	static coordinate_transform& instance();

	[[nodiscard]] std::array<double, 3> transform(const char* src, const char* dst, const double& x, const double& y, const double& z)
	{
		const auto& get_proj_string = [](PJ_CONTEXT* ctx, const char* epsg_code) ->std::string
		{
			std::unique_ptr<PJ, decltype(&proj_destroy)> pj(proj_create(ctx, std::format("EPSG:{}", epsg_code).c_str()), proj_destroy);
			if (pj == nullptr)
			{
				std::cout << std::format("Failed to create PJ for EPSG: {}\n", epsg_code);
				return "";
			}
			
			double boundary[4]{};
			const char* string_array;
			proj_get_area_of_use(ctx, pj.get(), &boundary[0], &boundary[1], &boundary[2], &boundary[3], &string_array);

			const std::string& proj_string = proj_as_proj_string(ctx, pj.get(), PJ_PROJ_5, nullptr);
			
			return proj_string;
		};

		{
			decltype(mtx)::scoped_lock sl;
			sl.acquire(mtx, true);
			if (!trans_objects.contains(std::forward_as_tuple(src, dst)))
			{
				const auto& src_proj = get_proj_string(ctx, src);
				const auto& dst_proj = get_proj_string(ctx, dst);

				std::shared_ptr<PJ> trans_obj(proj_create_crs_to_crs(ctx, src_proj.c_str(), dst_proj.c_str(), nullptr), proj_destroy);
				trans_objects.emplace(std::forward_as_tuple(src, dst), trans_obj);
			}
			sl.release();
		}

		const auto& trans_object = trans_objects[std::forward_as_tuple(src, dst)];

		// from src to dst
		PJ_COORD from = proj_coord(x, y, z, 0.0);
		PJ_COORD to = proj_trans(trans_object.get(), PJ_DIRECTION::PJ_FWD, from);


		if (proj_errno(trans_object.get()) != 0)
		{
			std::cout << std::format("Failed proj_trans : {}\n", proj_errno_string(proj_errno(trans_object.get())));
			return {};
		}

		return { to.xyz.x, to.xyz.y, to.xyz.z };
	}

	[[nodiscard]] inline std::array<double, 3> transform(const char* src, const char* dst, const std::span<double, 3>& coord) { return transform(src, dst, coord[0], coord[1], coord[2]); }
};

#endif COORDINATE_TRANSFORM_DEFINITION

