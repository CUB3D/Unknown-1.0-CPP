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

Unknown::Graphics::Image* image = NULL;
Unknown::Graphics::Image player("Player.png");
Unknown::Graphics::ImageSprite playerSprite(10, 10, &player);

void render()
{
	image->render(100, 100);
	playerSprite.render();
}

void update()
{
	playerSprite.setAngle(0);
	playerSprite.move(1, 1);
}

void init()
{
	for (int i = 0; i < 2; i++)
	{
		image = UK_LOAD_IMAGE("Test.bmp");
	}
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