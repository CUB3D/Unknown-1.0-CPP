#include "stdafx.h"
#include "Physics.h"

bool Unknown::isAABBIntersecting(AABB a, AABB b)
{
	if (a.location.x > b.location.x + b.size.width)
	{
		return false;
	}

	if (a.location.x + a.size.width < b.location.x)
	{
		return false;
	}

	if (a.location.y > b.location.y + b.size.height)
	{
		return false;
	}

	if (a.size.height + a.location.y < b.location.y)
	{
		return false;
	}

	return true;
}