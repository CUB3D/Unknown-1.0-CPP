// Unknown Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "../Unknown 1.0++/Colour.h"
#include "../Unknown 1.0++/Map.h"
#include "../Unknown 1.0++/Image.h"
#include "../Unknown 1.0++/Sprite.h"
#include "../Unknown 1.0++/Input.h"
#include "../Unknown 1.0++/Entity.h"
#include "../Unknown 1.0++/Physics.h"
#include "../Unknown 1.0++/Loader.h"
#include "../Unknown 1.0++/Animation.h"
#include "../Unknown 1.0++/Font.h"
#include "../Unknown 1.0++/Particle.h"
#include "../Unknown 1.0++/Quadtree.h"
#include "../Unknown 1.0++/UI.h"
#include "../Unknown 1.0++/Image.h"
#include "../Unknown 1.0++/Unknown.h"
#include "../Unknown 1.0++/Log.h"

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

Unknown::UIContainer UI;

void render()
{
	UI.renderUI();
}

void update()
{
	e->sprite->setAngle(45);
	//e->sprite->move(-1, -1);

	//std::cout << tree.NW.entitys.size() << std::endl;

	//tree.updateEntity(e);

	//tree.handleAllCollisions();

	using namespace Unknown;

	if (getKeyState("MoveUp"))
	{
		printf("MoveUP pressed\n");
	}
}

void testCollisionListener(Unknown::Entity* ent, Unknown::Entity* ent2)
{
	//std::cout << "Test" << std::endl;
}

void init()
{
	Unknown::log(0, "This is an infomation log");

	e = new Ent(new Unknown::Graphics::ImageSprite(30, 30, &font_img), "A");
	Ent* ee = new Ent(new Unknown::Graphics::ImageSprite(300, 300, new Unknown::Graphics::Image("Font.png")), "B");
	//tree.addEnity(e)
	//tree.addEnity(ee);
	Unknown::registerEntity(e);
	Unknown::registerEntity(ee);

	Unknown::registerEntityCollision(e->getEntityID(), ee->getEntityID());

	UK_ADD_COLLISION_LISTENER_EXTERNAL(testCollisionListener, e->getEntityID());

	Unknown::registerKeybind(Unknown::KeyCode::KEY_UP, "MoveUp");

	UI = Unknown::Loader::loadUI("TestUI.json");
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