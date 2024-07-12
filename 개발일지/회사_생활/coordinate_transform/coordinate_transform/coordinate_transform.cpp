#include "build_config.h"
#include "coordinate_transform.hpp"

coordinate_transform::coordinate_transform() : ctx(proj_context_create())
{
	if (ctx == nullptr)
		throw std::exception("'coordinate_transform'.'cannot initialize proj_context'\n");

	const std::string path_string = target_config.mapping.proj_data_path.generic_string();
	const char* proj_data_path = path_string.c_str();
	proj_context_set_search_paths(ctx, 1, &proj_data_path);
}

coordinate_transform::~coordinate_transform()
{
	if (ctx != nullptr)
		proj_context_destroy(ctx);
}

coordinate_transform& coordinate_transform::instance()
{
	static coordinate_transform instance;
	return instance;
}
