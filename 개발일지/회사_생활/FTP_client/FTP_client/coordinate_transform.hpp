#pragma once
// std
#include <map>

// proj
#include <proj/coordinates.hpp>
#include <proj.h>

// oneTBB
#include <oneapi/tbb/queuing_rw_mutex.h>

#define COORDINATE_TRANSFORM_DEFINITION

#ifdef COORDINATE_TRANSFORM_DEFINITION

enum class coordinates
{
	c3857, c32652, c4326, c5186, c5187, c5179, c5714
};

static constexpr coordinates default_src_coord = coordinates::c4326;
static constexpr coordinates default_dst_coord = coordinates::c5186;
static const std::map<coordinates, const char* const> coord_info
{
	{ coordinates::c3857, "+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m +nadgrids=@null +no_defs" },
	{ coordinates::c4326, "+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs" },
	{ coordinates::c5186, "+proj=tmerc +lat_0=38 +lon_0=127 +k=1 +x_0=200000 +y_0=600000 +ellps=GRS80 +towgs84=0,0,0,0,0,0,0 +units=m +no_defs" },
	{ coordinates::c5187, "+proj=tmerc +lat_0=38 +lon_0=129 +k=1 +x_0=200000 +y_0=600000 +ellps=GRS80 +units=m +no_defs" },
	{ coordinates::c5179, "+proj=tmerc +lat_0=38 +lon_0=127.5 +k=0.9996 +x_0=1000000 +y_0=2000000 +ellps=GRS80 +units=m +no_defs" },
	{ coordinates::c5714, "+proj=longlat +datum=ETRS89 +no_defs" },
	{ coordinates::c32652, "+proj=utm +zone=52 +datum=WGS84 +units=m +no_defs" }
};

class coordinate_transform
{
	coordinate_transform();
	PJ_CONTEXT* ctx;
	std::map<std::tuple<coordinates, coordinates>, std::shared_ptr<PJ>> trans_objects;
	tbb::queuing_rw_mutex mtx;
public:
	~coordinate_transform();
	static coordinate_transform& instance();

	template<coordinates src, coordinates dst>
		requires (0 <= static_cast<int>(src) && static_cast<int>(src) < 7 && 0 <= static_cast<int>(dst) && static_cast<int>(dst) < 7)
	void transform(double& x, double& y, double& z)
	{
		if constexpr (src == dst)
			return;
		{
			decltype(mtx)::scoped_lock sl;
			sl.acquire(mtx, true);
			if (!trans_objects.contains(std::forward_as_tuple(src, dst)))
			{
				const auto& src_coord_string = coord_info.at(src);
				const auto& dst_coord_string = coord_info.at(dst);

				std::shared_ptr<PJ> trans_obj(proj_create_crs_to_crs(ctx, src_coord_string, dst_coord_string, nullptr), proj_destroy);
				trans_objects.emplace(std::forward_as_tuple(src, dst), trans_obj);
			}
			sl.release();
		}
		const auto& trans_object = trans_objects[std::forward_as_tuple(src, dst)];
		
		// from src to dst
		PJ_COORD from = proj_coord(x, y, z, 0.0);
		PJ_COORD to = proj_trans(trans_object.get(), PJ_DIRECTION::PJ_FWD, from);

		x = to.xyz.x;
		y = to.xyz.y;
		z = to.xyz.z;
	}
	template<coordinates src, coordinates dst>
		requires (0 <= static_cast<int>(src) && static_cast<int>(src) < 7 && 0 <= static_cast<int>(dst) && static_cast<int>(dst) < 7)
	inline void transform(double(&coord)[3]) { transform<src, dst>(coord[0], coord[1], coord[2]); }
};

#endif COORDINATE_TRANSFORM_DEFINITION

