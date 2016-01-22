// Unknown Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <Unknown.h>

#include "UI2D.h"
#include <iostream>
#include "Colour.h"
#include "Map.h"
#include "Image.h"
#include "Sprite.h"
#include "Input.h"
#include "Entity.h"
#include "Physics.h"
#include "Loader.h"
#include "Animation.h"
#include "Font.h"
#include "Particle.h"
#include "Quadtree.h"

Unknown::Graphics::Image font_img("Font.png");

Unknown::Quadtree tree;

class Ent : public Unknown::TwoStateEntity
{
public:
	std::string str;

	Ent(Unknown::Sprite* sprite, std::string str0) : TwoStateEntity(sprite), str(str0)
	{

	}

	const std::string getEntityID() const
	{
		return str;
	}
};

Ent* e;

void render()
{
	tree.handleAllCollisions();
}

void update()
{
	e->sprite->setAngle(45);
	e->sprite->move(-1, -1);
}

void testCollisionListener(Unknown::Entity* ent, Unknown::Entity* ent2)
{
	std::cout << "Test" << std::endl;
}

void init()
{
	e = new Ent(new Unknown::Graphics::ImageSprite(330, 330, &font_img), "A");
	Ent* ee = new Ent(new Unknown::Graphics::ImageSprite(300, 300, new Unknown::Graphics::Image("Font.png")), "B");
	tree.addEnity(e);
	tree.addEnity(ee);
	Unknown::registerEntity(e);
	Unknown::registerEntity(ee);

	Unknown::registerEntityCollision(e->getEntityID(), ee->getEntityID());

	UK_ADD_COLLISION_LISTENER_EXTERNAL(testCollisionListener, e->getEntityID());
}

int _tmain(int argc, _TCHAR* argv[])
{
	UK_UPDATE(update);
	UK_RENDER(render);

	UK_CREATE_WINDOW();

	init();

	UK_INIT_GAME();

	return 0;
}