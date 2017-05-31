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

std::unique_ptr<Unknown::Map> map;
Unknown::Timer timer(0.2);

int width = 128;
int height = 8;
bool started = false;
bool creatingBoard = false;

void createBoard();

void createBoard()
{
    map = std::unique_ptr<Unknown::Map>(new Unknown::Map(width, height));

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

    printf("Board creation complete\n");
}

void render()
{
    if (creatingBoard)
    {
        return;
    }
	int scaleX = 1024/width;
    int scaleY = 1024/height;

    for(int x = 0; x <  map->mapSize->width; x++)
    {
        for (int y = 0; y <  map->mapSize->height; y++)
        {
            if(map->getTileID(x, y) == 0)
            {
                UK_DRAW_RECT(x*scaleX, y*scaleY, scaleX, scaleY, Unknown::Colour::WHITE);
            }
            else
            {
                UK_DRAW_RECT(x*scaleX, y*scaleY, scaleX, scaleY, Unknown::Colour::BLACK);
            }
        }
    }

    if(!started)
    {
        startMenu.renderUI();
    }
}

int checkTile(int x, int y, std::unique_ptr<Unknown::Map>& map)
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

void keylistener(Unknown::KeyEvent evnt)
{
    if(evnt.keyState == Unknown::InputState::RELEASED)
    {
        if(started)
        {
            if(evnt.SDLCode == SDLK_LEFT)
            {
                timer.timerSpeed += 100;
                if(timer.timerSpeed > 1000)
                {
                    timer.timerSpeed = 1000;
                }
                printf("Timer speed now %d\n", timer.timerSpeed);
            }
            else
            {
                if(evnt.SDLCode == SDLK_RIGHT)
                {
                    timer.timerSpeed -= 20;
                    if(timer.timerSpeed <= 0)
                    {
                        timer.timerSpeed = 20;
                    }
                    printf("Timer speed now %d\n", timer.timerSpeed);
                }
                else
                {
                    if(evnt.SDLCode == SDLK_ESCAPE)
                    {
                        started = false;
                        auto textBoxSizeContent = startMenu.getComponentByName("TextLabelTextBoxSizeContent");
                        (*textBoxSizeContent)->content = "";
                    }
                }
            }
        }
        else
        {
            if (evnt.SDLCode == SDLK_ESCAPE)
            {
                started = true;
            }
        }
    }
}

void UICallback(const Unknown::UIEvent evnt)
{
    if(evnt.componentName == "ButtonStart")
    {
        auto textBoxSize = startMenu.getComponentByName("TextBoxSize");

        if ((*textBoxSize)->content.size() > 0)
        {
            int boardSize = std::stoi((*textBoxSize)->content);
            printf("Creating board with size %d\n", boardSize);
            width = height = boardSize;
            started = true;
            createBoard();
        }
    }

    if(evnt.componentName == "TextBoxSize")
    {
        if(!Unknown::isCharCodeNumber(*evnt.relatedKey))
        {
            (*evnt.relatedKey) = "";
        }
    }
}

void update()
{
    using namespace Unknown;

    std::unique_ptr<Unknown::Map> newMap = std::unique_ptr<Unknown::Map>(new Map(width, height));

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

        map = std::move(newMap);
    }
}

void init()
{
	srand(time(NULL));
	UK_LOG_INFO_VERBOSE("This is an information log");
    UK_ADD_KEY_LISTENER_EXTERNAL(keylistener, "mainmenu");
    UK_ADD_UI_LISTENER_EXTERNAL(UICallback, "mainmenu");

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
