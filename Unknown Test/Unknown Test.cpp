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

Unknown::Graphics::Image font_img("Font.png");
//Unknown::Graphics::Particle part(new Unknown::Graphics::ImageSprite(10, 10, &font_img), 10);

class Ent : public Unknown::TwoStateEntity
{
public:
	std::string s;

	Ent(Unknown::Sprite* spr, std::string str) : Unknown::TwoStateEntity(spr)
	{
		s = str;
	}

	const std::string getEntityID() const
	{
		return s;
	}
};

Ent* ent1;
Ent* ent2;

void render()
{
	//part.render();
}

void update()
{
	//part.update();

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_DOWN))
	{
		ent2->sprite->move(0, 1);
	}

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_UP))
	{
		ent2->sprite->move(0, -1);
	}

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_RIGHT))
	{
		ent2->sprite->move(1, 0);
	}

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_LEFT))
	{
		ent2->sprite->move(-1, 0);
	}
}

void init()
{
	ent1 = new Ent(new Unknown::Graphics::ImageSprite(10, 10, new Unknown::Graphics::Image("Player.png")), "EntA");
	ent2 = new Ent(new Unknown::Graphics::ImageSprite(10, 10, new Unknown::Graphics::Image("Player.png")), "EntB");

	UK_REGISTER_ENTITY(ent1);
	UK_REGISTER_ENTITY(ent2);

	Unknown::registerEntityCollision("EntA", "EntB");
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