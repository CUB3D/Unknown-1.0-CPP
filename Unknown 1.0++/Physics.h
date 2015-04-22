#ifndef PHYSICS_H
#define PHYSICS_H

#include "Utils.h"

namespace Unknown
{
	struct AABB
	{
		Point location;
		Dimension size;
	};

	bool isAABBIntersecting(AABB a, AABB b);
}

#endif