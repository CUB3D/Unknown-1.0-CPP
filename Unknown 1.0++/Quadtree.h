#pragma once

#include "Entity.h"
#include <vector>

namespace Unknown
{
	struct Quad
	{
		std::vector<Entity*> entitys;

		void renderContents();
	};

	class Quadtree
	{
	public:
		Quadtree();

		Quad NW;
		Quad NE;
		Quad SW;
		Quad SE;
	};

}