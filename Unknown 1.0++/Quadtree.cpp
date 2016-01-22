#include "stdafx.h"
#include "Quadtree.h"
#include "Entity.h"
#include "Physics.h"

void Unknown::Quad::handleCollisions()
{
	for (int i = 0; i < this->entitys.size(); i++)
	{
		Entity* ent1 = this->entitys[i];

		if (ent1->isAlive())
		{
			for (int i = 0; i < this->entitys.size(); i++)
			{
				Entity* ent2 = this->entitys[i];

				if (ent2->isAlive())
				{
					if (entityColisionLookup.find(ent1->getEntityID()) != entityColisionLookup.end())
					{
						std::vector<std::string> colliders = entityColisionLookup[ent1->getEntityID()];
						if (std::find(colliders.begin(), colliders.end(), ent2->getEntityID()) != colliders.end())
						{
							if (isAABBIntersecting(ent1->sprite->bounds, ent2->sprite->bounds))
							{
								std::vector<std::function<void(Entity*, Entity*)>> colliders = collisionHooks[ent1->getEntityID()];

								std::vector<std::function<void(Entity*, Entity*)>>::iterator itter = colliders.begin();

								for (; itter != colliders.end(); itter++)
								{
									(*itter)(ent1, ent2);
								}
							}
						}
					}
				}
			}
		}
	}
}


Unknown::Quadtree::Quadtree()
{

}

void Unknown::Quadtree::init()
{
	this->NW.quadBounds.location.x = 0;
	this->NW.quadBounds.location.y = 0;
	this->NW.quadBounds.size.height = UK_GET_SCREEN_SIZE()->height / 2;
	this->NW.quadBounds.size.width = UK_GET_SCREEN_SIZE()->width / 2;

	this->NE.quadBounds.location.x = UK_GET_SCREEN_SIZE()->height / 2;
	this->NE.quadBounds.location.y = 0;
	this->NE.quadBounds.size.height = UK_GET_SCREEN_SIZE()->height / 2;
	this->NE.quadBounds.size.width = UK_GET_SCREEN_SIZE()->width / 2;

	this->SE.quadBounds.location.x = 0;
	this->SE.quadBounds.location.y = UK_GET_SCREEN_SIZE()->height / 2;
	this->SE.quadBounds.size.height = UK_GET_SCREEN_SIZE()->height / 2;
	this->SE.quadBounds.size.width = UK_GET_SCREEN_SIZE()->width / 2;

	this->SW.quadBounds.location.x = UK_GET_SCREEN_SIZE()->height / 2;
	this->SW.quadBounds.location.y = UK_GET_SCREEN_SIZE()->height / 2;
	this->SW.quadBounds.size.height = UK_GET_SCREEN_SIZE()->height / 2;
	this->SW.quadBounds.size.width = UK_GET_SCREEN_SIZE()->width / 2;

	this->hasInit = true;
}

void Unknown::Quadtree::addEnity(Entity* ent)
{
	if (!this->hasInit)
	{
		init();
	}

	if (isAABBIntersecting(ent->sprite->bounds, this->NE.quadBounds))
	{
		this->NE.entitys.push_back(ent);
	}

	if (isAABBIntersecting(ent->sprite->bounds, this->NW.quadBounds))
	{
		this->NW.entitys.push_back(ent);
	}

	if (isAABBIntersecting(ent->sprite->bounds, this->SE.quadBounds))
	{
		this->SE.entitys.push_back(ent);
	}

	if (isAABBIntersecting(ent->sprite->bounds, this->SW.quadBounds))
	{
		this->SW.entitys.push_back(ent);
	}
}

void Unknown::Quadtree::handleAllCollisions()
{
	this->NE.handleCollisions();
	this->NW.handleCollisions();
	this->SE.handleCollisions();
	this->SW.handleCollisions();
}

void Unknown::Quadtree::updateEntity(Entity* ent)
{
}
