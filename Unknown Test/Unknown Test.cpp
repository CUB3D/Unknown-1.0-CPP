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

Unknown::Graphics::Animation* animation;

Unknown::Graphics::AnimatedSprite* animationTest;

void render()
{
	animationTest->render();

	SDL_SetRenderDrawColor(Unknown::getUnknown()->windowRenderer, 0xff, 0xff, 00, 0xFF);
	UK_DRAW_RECT(100, 100, 100, 100, Unknown::Colour::RED);
	SDL_SetRenderDrawColor(Unknown::getUnknown()->windowRenderer, 00, 00, 00, 00);
	//player.render(100, 100);
}

void update()
{
}

void init()
{
	animation = new Unknown::Graphics::Animation();

	animation->addFrame(&image, 1000);
	animation->addFrame(&player, 1000);

	animationTest = new Unknown::Graphics::AnimatedSprite(20, 20, animation);
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