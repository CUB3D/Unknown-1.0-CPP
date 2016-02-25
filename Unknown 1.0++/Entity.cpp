#include "stdafx.h"
#include "Entity.h"

#include <iostream>
#include <algorithm>
#include <string.h>

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


::Unknown::Entity* Unknown::Entity::clone() const
{
	Entity* ent = (Entity*)malloc(sizeof(Entity));
	memcpy(ent, this, sizeof(Entity));
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

::Unknown::Entity* Unknown::TwoStateEntity::clone() const
{
	TwoStateEntity* ent = (TwoStateEntity*)malloc(sizeof(TwoStateEntity));
	memcpy(ent, this, sizeof(TwoStateEntity));
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

::Unknown::Entity* Unknown::HealthEntity::clone() const
{
	HealthEntity* ent = (HealthEntity*)malloc(sizeof(HealthEntity));
	memcpy(ent, this, sizeof(HealthEntity));
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

std::map<std::string, std::vector<std::function<void(Unknown::Entity*, Unknown::Entity*)>>> Unknown::collisionHooks;

void Unknown::registerCollisionListener(std::function<void(Entity*, Entity*)> handler, std::string entityID)
{
	if (collisionHooks.find(entityID) != collisionHooks.end())
	{
		collisionHooks[entityID].push_back(handler);
	}
	else
	{
		std::vector<std::function<void(Entity*, Entity*)>> handlers;

		handlers.push_back(handler);

		collisionHooks[entityID] = handlers;
	}
}