#ifndef PHYSICS_H
#define PHYSICS_H

#include "Utils.h"

namespace Unknown
{
	struct AABB
	{
		Point<double> location;
		Dimension<double> size;
	};

	bool isAABBIntersecting(AABB a, AABB b);
}

#endif