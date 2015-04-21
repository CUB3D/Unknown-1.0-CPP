#include "stdafx.h"
#include "Entity.h"

#include "Sprite.h"

Unknown::Entity::Entity(Sprite* sprite)
{
	this->sprite = sprite;
}


Unknown::Entity::~Entity()
{
	delete sprite;
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

// TwoStateEntity class

Unknown::TwoStateEntity::TwoStateEntity(Sprite* sprite) : Entity(sprite)
{
}

Unknown::TwoStateEntity::~TwoStateEntity()
{
	delete sprite;
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

Unknown::HealthEntity::~HealthEntity()
{
	delete sprite;
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


