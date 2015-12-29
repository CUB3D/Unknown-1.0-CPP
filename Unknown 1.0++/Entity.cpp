#include "stdafx.h"
#include "Entity.h"

#include "Sprite.h"
#include "Unknown.h"
#include "Physics.h"

#include <iostream>
#include <algorithm>

Unknown::Entity::Entity(Sprite* sprite)
{
	this->sprite = sprite;
}


Unknown::Entity::~Entity()
{
}

void Unknown::Entity::update()
{
}

void Unknown::Entity::render() const
{
	if (this->isAlive())
	{
		this->sprite->render();
	}
}

bool Unknown::Entity::isAlive() const
{
	return false;
}

void Unknown::Entity::kill()
{
}

void Unknown::Entity::damage(const int damage)
{
}

void Unknown::Entity::heal(const int health)
{
}

const std::string Unknown::Entity::getEntityID() const
{
	return "Entity";
}

void Unknown::Entity::handleCollision(Entity* ent)
{
}

Unknown::Entity* Unknown::Entity::clone() const
{
	Entity* ent = (Entity*)malloc(sizeof Entity);
	memcpy(ent, this, sizeof Entity);
	return ent;
}

// TwoStateEntity class

Unknown::TwoStateEntity::TwoStateEntity(Sprite* sprite) : Entity(sprite)
{
}

bool Unknown::TwoStateEntity::isAlive() const
{
	return this->alive;
}

void Unknown::TwoStateEntity::kill()
{
	this->alive = false;
}

void Unknown::TwoStateEntity::damage(const int damage)
{
	this->kill();
}

void Unknown::TwoStateEntity::heal(const int health)
{
	if (health > 0)
		this->alive = true;
}

Unknown::Entity* Unknown::TwoStateEntity::clone() const
{
	TwoStateEntity* ent = (TwoStateEntity*)malloc(sizeof TwoStateEntity);
	memcpy(ent, this, sizeof TwoStateEntity);
	return ent;
}

// HealthEntity class

Unknown::HealthEntity::HealthEntity(Sprite* sprite, int health) : Entity(sprite)
{
	this->health = health;
	this->maxHealth = health;
}

Unknown::HealthEntity::HealthEntity(Sprite* sprite, int health, int maxHealth) : Entity(sprite)
{
	this->health = health;
	this->maxHealth = maxHealth;
}

bool Unknown::HealthEntity::isAlive() const
{
	return this->health > 0;
}

void Unknown::HealthEntity::kill()
{
	this->health = 0;
}

void Unknown::HealthEntity::damage(const int damage)
{
	this->health -= damage;

	if (this->health < 0)
		this->health = 0;
}

void Unknown::HealthEntity::heal(const int health)
{
	this->health += health;

	if (this->health > this->maxHealth)
		this->health = this->maxHealth;
}

int Unknown::HealthEntity::getHealth() const
{
	return this->health;
}

Unknown::Entity* Unknown::HealthEntity::clone() const
{
	HealthEntity* ent = (HealthEntity*)malloc(sizeof HealthEntity);
	memcpy(ent, this, sizeof HealthEntity);
	return ent;
}

std::vector<Unknown::Entity*> Unknown::entitys;
bool Unknown::hasEntityInit = false;

void Unknown::initEntitys()
{
	registerHook(renderEntitys, HookType::RENDER);
	registerHook(updateEntitys, HookType::UPDATE);

	hasEntityInit = true;
}

void Unknown::registerEntity(Entity* ent)
{
	if (!hasEntityInit)
		initEntitys();

	entitys.push_back(ent);
}

void Unknown::updateEntitys()
{
	for (int i = 0; i < entitys.size(); i++)
	{
		entitys[i]->update();
	}

	// collision check

	for (int i = 0; i < entitys.size(); i++)
	{
		Entity* ent1 = entitys[i];

		if (ent1->isAlive())
		{
			for (int i = 0; i < entitys.size(); i++)
			{
				Entity* ent2 = entitys[i];

				if (ent2->isAlive())
				{
					if (entityColisionLookup.find(ent1->getEntityID()) != entityColisionLookup.end())
					{
						std::vector<std::string> colliders = entityColisionLookup[ent1->getEntityID()];
						if (std::find(colliders.begin(), colliders.end(), ent2->getEntityID()) != colliders.end())
						{
							if (isAABBIntersecting(ent1->sprite->bounds, ent2->sprite->bounds))
							{
								ent1->handleCollision(ent2);

								std::cout << "Test for collison patch" << std::endl;
							}
						}
					}
				}
			}
		}
	}
}

void Unknown::renderEntitys()
{
	for (int i = 0; i < entitys.size(); i++)
	{
		entitys[i]->render();
	}
}

std::map<std::string, std::vector<std::string>> Unknown::entityColisionLookup;

void Unknown::registerEntityCollision(std::string base, std::string collider)
{
	if (entityColisionLookup.find(base) != entityColisionLookup.end())
	{
		entityColisionLookup[base].push_back(collider);
	}
	else
	{
		std::vector<std::string> colliders;

		colliders.push_back(collider);

		entityColisionLookup[base] = colliders;
	}
}