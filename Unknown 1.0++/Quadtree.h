#pragma once

#include "Entity/Entity.h"
#include <vector>
#include "Utils.h"

namespace Unknown
{
	struct Quad
	{
		std::vector<Entity*> entitys;

		//AABB quadBounds;

		void handleCollisions();
	};

	class Quadtree
	{
	private:
		bool hasInit;

	public:
		Quadtree();

		Quad NW;
		Quad NE;
		Quad SW;
		Quad SE;

		void init();

		void addEnity(Entity* entity);

		void handleAllCollisions();

		void updateEntity(Entity* entity);
	};

}