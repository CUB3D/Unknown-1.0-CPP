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

	UK_DRAW_RECT(100, 100, 100, 100, Unknown::Colour::RED);

	player.render(200, 200, 45);
}

void update()
{
}

void init()
{
	animation = UK_LOAD_ANIMATION("Animation.json");

	animationTest = new Unknown::Graphics::AnimatedSprite(20, 20, animation);

	animationTest->setAngle(45);
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