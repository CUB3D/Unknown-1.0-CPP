#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"

namespace Unknown
{
	class Entity
	{
	public:
		Sprite* sprite;

		Entity(Sprite* sprite);
		~Entity();

		virtual void update();
		virtual void render() const;

		virtual bool isAlive() const;
		virtual void kill();
		virtual void damage(const int damage);
		virtual void heal(const int health);

		virtual const std::string getEntityID() const;
	};

	class TwoStateEntity : public Entity
	{
	private:
		bool alive = true;

	public:
		TwoStateEntity(Sprite* sprite);
		~TwoStateEntity();

		virtual bool isAlive() const;
		virtual void kill();
		virtual void damage(const int damage);
		virtual void heal(const int health);
	};

	class HealthEntity : public Entity
	{
	private:
		int health;
		int maxHealth;

	public:
		HealthEntity(Sprite* sprite, int health);
		HealthEntity(Sprite* sprite, int health, int maxHealth);
		~HealthEntity();

		virtual bool isAlive() const;
		virtual void kill();
		virtual void damage(const int damage);
		virtual void heal(const int health);

		int getHealth() const;
	};
}

#endif

