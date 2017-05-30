// Unknown Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

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
#include "UI.h"
#include "UI2D.h"
#include "Image.h"
#include "Unknown.h"
#include "Log.h"
#include "PythonScript.h"
#include "Timer.h"

#include <Python.h>
#include <cmath>

Unknown::Graphics::Image font_img("Font.png");
Unknown::Graphics::Font* font;

Unknown::UIContainer startMenu;

Unknown::Map* map;
Unknown::Timer timer;

int SIZE = 128;
bool started = false;

void createBoard()
{
    map = new Unknown::Map(SIZE, SIZE);

    for(int x = 0; x < map->mapSize->width; x++)
    {
        for(int y = 0; y < map->mapSize->height; y++)
        {
            if(rand()%2 == 1) {
                map->setTileID(0, x, y);
            }
            else {
                map->setTileID(1, x, y);
            }
        }
    }
}

void render()
{
	int scale = 512/SIZE;

    for(int x = 0; x <  map->mapSize->width; x++)
    {
        for (int y = 0; y <  map->mapSize->height; y++)
        {
            if(map->getTileID(x, y) == 0)
            {
                UK_DRAW_SQUARE(x*scale, y*scale, scale, Unknown::Colour::WHITE);
            }
            else
            {
                UK_DRAW_SQUARE(x*scale, y*scale, scale, Unknown::Colour::BLACK);
            }
        }
    }

    if(!started)
    {
        startMenu.renderUI();
    }
}

int checkTile(int x, int y, Unknown::Map* map)
{
	if(x < 0 || y < 0 || x >  map->mapSize->width || y > map->mapSize->height)
	{
		return 0;
	}
	else
	{
		return map->getTileID(x, y);
	}
}

bool isCharCodeNumber(const char* key)
{
	return *key >= '0' && *key <= '9';
}

void keylistener(Unknown::KeyEvent evnt)
{
    if(evnt.keyState == Unknown::InputState::RELEASED)
    {
        if(started)
        {
            if(evnt.SDLCode == SDLK_LEFT)
            {
                timer.timerSpeed = 1000/20;
            }
            else
            {
                if(evnt.SDLCode == SDLK_RIGHT)
                {
                    timer.timerSpeed = 1;
                }
            }
        }
        else
        {
            if (evnt.SDLCode == SDLK_RETURN)
            {
				auto textBoxSizeContent = startMenu.getComponentByName("TextLabelTextBoxSizeContent");
				
				int boardSize = std::stoi((*textBoxSizeContent)->content);
				printf("Creating board with size %d\n", boardSize);
				SIZE = boardSize;
				started = true;
				createBoard();
            } else
            {
				auto textBoxSizeContent = startMenu.getComponentByName("TextLabelTextBoxSizeContent");
				const char *key = SDL_GetKeyName(evnt.SDLCode);
                    
                if (evnt.SDLCode == SDLK_BACKSPACE)
                {
                    if ((*textBoxSizeContent)->content.size() > 0)
                    {
                        (*textBoxSizeContent)->content.pop_back();
                    }
                } else
                {
					if(isCharCodeNumber(key))
					{
                        (*textBoxSizeContent)->content += key;
                    }
                }
            }
        }
    }
}

void update()
{
    using namespace Unknown;

    Map *newMap = new Map(SIZE, SIZE);

    if (timer.isTickComplete())
    {
        for (int x = 0; x <  map->mapSize->width; x++)
        {
            for (int y = 0; y <  map->mapSize->height; y++)
            {
                int alive = map->getTileID(x, y);
                int popcount = 0;
                popcount += checkTile(x - 1, y - 1, map);
                popcount += checkTile(x - 1, y, map);
                popcount += checkTile(x - 1, y + 1, map);

                popcount += checkTile(x, y - 1, map);
                popcount += checkTile(x, y + 1, map);

                popcount += checkTile(x + 1, y - 1, map);
                popcount += checkTile(x + 1, y, map);
                popcount += checkTile(x + 1, y + 1, map);

                if (alive)
                {
                    if (popcount < 2 || popcount > 3)
                    {
                        newMap->setTileID(0, x, y);
                    } else
                    {
                        if (popcount == 2 || popcount == 3)
                        {
                            newMap->setTileID(1, x, y);
                        }
                    }
                } else
                {
                    if (popcount == 3)
                    {
                        newMap->setTileID(1, x, y);
                    } else
                    {
                        newMap->setTileID(0, x, y);
                    }
                }
            }
        }

        delete map;

        map = newMap;
    }
}

void init()
{
	srand(time(NULL));
	UK_LOG_INFO_VERBOSE("This is an information log");
    UK_ADD_KEY_LISTENER_EXTERNAL(keylistener, "mainmenu");

    createBoard();

    font = new Unknown::Graphics::Font(&font_img, "ABCDEFGHIJKLMNOPQRSTUVWXYZ: 1234567890", 16);

    startMenu = Unknown::Loader::loadUI("MainMenuUI.json");
	startMenu.setGlobalFont(font);

    //UK_PYTHON_LOAD_SCRIPT("Test");
}

#ifdef _WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	UK_UPDATE(update);
	UK_RENDER(render);

	UK_CREATE_WINDOW();

	init();

	UK_INIT_GAME();

	return 0;
}
