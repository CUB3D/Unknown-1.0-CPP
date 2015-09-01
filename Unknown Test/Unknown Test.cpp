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

Unknown::Graphics::Image player("Player.png");
Unknown::Graphics::ImageSprite playerSprite(10, 10, &player);

int i = 0;

void render()
{
}

void update()
{
	i++;

	if (i == 200)
	{
		std::cout << "Removing listener" << std::endl;

		::Unknown::removeMouseListener("Test_listener");
	}
}

class Test
{
public:
	Test()
	{
		UK_ADD_MOUSE_LISTENER(onMouseClick, "Test_listener");
	}

	void onMouseClick(Unknown::MouseEvent evnt)
	{
		std::cout << "Click" << std::endl;
	}
};

void init()
{
	Test t;
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