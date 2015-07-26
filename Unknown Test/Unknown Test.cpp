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

Unknown::AABB a;
Unknown::AABB b;

Unknown::Entity* sprite;

bool bb;

void render()
{
	if (bb)
	{
		UK_DRAW_RECT(a.location.x, a.location.y, a.size.width, a.size.height, UK_COLOUR_RGB(255, 0, 0));
	}
	else
	{
		UK_DRAW_RECT(a.location.x, a.location.y, a.size.width, a.size.height, UK_COLOUR_RGB(0, 255, 0));
	}
	UK_DRAW_RECT(b.location.x, b.location.y, b.size.width, b.size.height, UK_COLOUR_RGB(255, 255, 0));
}

void update()
{
	if (Unknown::getKeyState(Unknown::KeyCode::KEY_RIGHT))
	{
		a.location.x++;
	}

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_LEFT))
	{
		a.location.x--;
	}

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_UP))
	{
		a.location.y--;
	}

	if (Unknown::getKeyState(Unknown::KeyCode::KEY_DOWN))
	{
		a.location.y++;
	}

	bb = Unknown::isAABBIntersecting(a, b);
}

void init()
{
	a.location.x = 10;
	a.location.y = 30;

	a.size.width = 50;
	a.size.height = 50;

	b.location.x = 40;
	b.location.y = 60;

	b.size.width = 25;
	b.size.height = 40;
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