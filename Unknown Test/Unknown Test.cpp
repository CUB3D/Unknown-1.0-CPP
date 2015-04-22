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

using namespace Unknown::Graphics;

ImageSprite tst(50, 50, new Image("Player.png"));

Unknown::Entity* ent = new Unknown::TwoStateEntity(&tst);

void render()
{
	UK_REGISTER_ENTITY(ent);
}

void update()
{
}

int _tmain(int argc, _TCHAR* argv[])
{
	UK_UPDATE(update);
	UK_RENDER(render);

	UK_CREATE_WINDOW("Test", 100, 100);

	UK_INIT_GAME();

	return 0;
}