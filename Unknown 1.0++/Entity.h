#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include <functional>
#include <map>

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

		virtual Entity* clone() const;
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

		virtual Entity* clone() const;
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

		virtual Entity* clone() const;
	};

	extern std::vector<Entity*> entitys;
	extern bool hasEntityInit;

	void initEntitys();

	void registerEntity(Entity* ent);
	void updateEntitys();
	void renderEntitys();

#define UK_REGISTER_ENTITY(x) Unknown::registerEntity(x);

	extern std::map<std::string, std::vector<std::string>> entityColisionLookup;

	void registerEntityCollision(std::string base, std::string collider);

	extern std::map<std::string, std::vector<std::function<void(Entity*, Entity*)>>> collisionHooks;

	void registerCollisionListener(std::function<void(Entity*, Entity*)> handler, std::string entityID);

#define UK_ADD_COLLISION_LISTENER_INTERNAL(listener, id) ::Unknown::registerCollisionListener([this](::Unknown::Entity* ent1, ::Unknown::Entity* ent2) {listener(ent1, ent2);}, id)
#define UK_ADD_COLLISION_LISTENER_EXTERNAL(listener, id) ::Unknown::registerCollisionListener([](::Unknown::Entity* ent1, ::Unknown::Entity* ent2) {listener(ent1, ent2);}, id)
}

#endif

