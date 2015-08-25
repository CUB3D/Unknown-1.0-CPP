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

Unknown::Graphics::Image image("Test.bmp");
Unknown::Graphics::Image player("Player.png");
Unknown::Graphics::ImageSprite playerSprite(10, 10, &player);

void render()
{
	playerSprite.render();
}

void update()
{
	playerSprite.setAngle(0);
	playerSprite.move(1, 1);
}

void init()
{
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