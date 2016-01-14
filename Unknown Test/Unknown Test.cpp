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
#include "Quadtree.h"

Unknown::Graphics::Image font_img("Font.png");

Unknown::Quadtree tree;

void render()
{
	tree.NW.renderContents();
}

void update()
{
}

void init()
{
	Unknown::Entity* e = new Unknown::TwoStateEntity(new Unknown::Graphics::ImageSprite(20, 20, &font_img));
	tree.NW.entitys.push_back(e);
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