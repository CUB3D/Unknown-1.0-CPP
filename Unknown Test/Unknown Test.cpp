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

ImageSprite tst(0, 0, new Image("Player.png"));

Unknown::Entity* ent = new Unknown::HealthEntity(&tst, 100, 200);



void render()
{
	ent->render();
}

void update()
{
	ent->heal(1);

	std::cout << "H: " << ent->isAlive() << std::endl;
}

void onKey(const Unknown::KeyEvent evnt)
{
	switch (evnt.keyCode)
	{
	case Unknown::KeyCode::KEY_LEFT:
		tst.location.x--;
		break;
	case Unknown::KeyCode::KEY_RIGHT:
		tst.location.x++;
		break;
	case Unknown::KeyCode::KEY_UP:
		tst.location.y--;
		break;
	case Unknown::KeyCode::KEY_DOWN:
		tst.location.y++;
		break;
	default:
		break;
	}
}

void onClick(const Unknown::MouseEvent evnt)
{
	std::cout << "B: " << evnt.mouseButton << ", S: " << evnt.buttonState << ", SDL: " << evnt.SDLButtonCode << std::endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	UK_UPDATE(update);
	UK_RENDER(render);

	UK_KEY_LISTENER(onKey);
	UK_MOUSE_LISTENER(onClick);

	UK_CREATE_WINDOW("Test", 100, 100);

	UK_INIT_GAME();


	return 0;
}