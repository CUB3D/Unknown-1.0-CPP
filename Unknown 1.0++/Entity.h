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
		virtual ~Entity();

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

		virtual bool isAlive() const;
		virtual void kill();
		virtual void damage(const int damage);
		virtual void heal(const int health);

		int getHealth() const;
	};

	extern std::vector<Entity*> entitys;
	extern bool hasEntityInit;

	void initEntitys();

	void registerEntity(Entity* ent);
	void updateEntitys();
	void renderEntitys();

#define UK_REGISTER_ENTITY(x) Unknown::registerEntity(x);
}

#endif

