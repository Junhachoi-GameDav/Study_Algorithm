#include "coordinate_transform.hpp"

coordinate_transform::coordinate_transform() : ctx(proj_context_create())
{
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
