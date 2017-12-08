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
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Event/Event.h"
#include "Event/EventManager.h"

Unknown::Graphics::Font* font;

std::unique_ptr<Unknown::Map> map;
Unknown::Timer timer(0.2);

Unknown::SceneManager scenes;

int width = 64;
int height = 64;
int scaleX = 0;
int scaleY = 0;

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

    auto uk = Unknown::getUnknown();
    scaleX = uk->screenSize->width / width;
    scaleY = uk->screenSize->height / height;

    printf("Board creation complete\n");
}

int pixelScale = 2;

void renderSimulationBoard()
{
    for (int x = 0; x < map->mapSize->width; x++)
    {
        for (int y = 0; y < map->mapSize->height; y++)
        {
            if (map->getTileID(x, y) == 0)
            {
                UK_DRAW_RECT(x * scaleX, y * scaleY, scaleX, scaleY, Unknown::Colour::WHITE);
            } else
            {
                UK_DRAW_RECT(x * scaleX, y * scaleY, scaleX, scaleY, Unknown::Colour::BLACK);
            }

            // If the last tile has been drawn
            if(x == map->mapSize->width - 1)
            {
             //   UK_DRAW_RECT(0, y * scaleY, scaleX * width, 1, Unknown::Colour::BLUE);
            }
        }

       // UK_DRAW_RECT(x * scaleX, 0, 1, scaleY * height, Unknown::Colour::BLUE);
    }
}

void render()
{
    scenes.currentScene->render();

    UK_DRAW_RECT(Unknown::getUnknown()->screenSize->width - 200, 5, 200, 60, Unknown::Colour::WHITE);

    std::string fps = "FPS: ";
    fps += std::to_string(Unknown::getUnknown()->fps);
    font->drawString(fps, Unknown::getUnknown()->screenSize->width - font->getStringWidth(fps) - 10, 10);

    std::string frameTime = "FrameTime: ";
    frameTime += std::to_string(Unknown::getUnknown()->lastFrameTimeMS);
    font->drawString(frameTime, Unknown::getUnknown()->screenSize->width - font->getStringWidth(frameTime) - 10, 30);

    std::string updateTime = "UpdateTime: ";
    updateTime += std::to_string(Unknown::getUnknown()->lastUpdateTimeMS);
    font->drawString(updateTime, Unknown::getUnknown()->screenSize->width - font->getStringWidth(updateTime) - 10, 50);
}

int tileExists(int x, int y, std::unique_ptr<Unknown::Map>& map)
{
    if(x < 0 || y < 0 || x >=  map->mapSize->width || y >= map->mapSize->height)
    {
        return 0;
    }
    return 1;
}

int checkTile(int x, int y, std::unique_ptr<Unknown::Map>& map)
{
	if(tileExists(x, y, map))
	{
		return map->getTileID(x, y);
	}
    return 0;
}

void keylistener(Unknown::Event& evnt)
{
//    if(evnt.keyState == Unknown::InputState::RELEASED)
//    {
//        if(evnt.SDLCode == SDLK_ESCAPE)
//        {
//            if(scenes.currentScene->name == "Simulator")
//            {
//                scenes.loadScene("MainMenu");
//                Unknown::UIContainer& mainMenu = scenes.getScene<Unknown::MenuScene>()->menu;
//                auto textBoxWidth = mainMenu.getComponentByName("TextBoxWidth");
//                auto textBoxHeight = mainMenu.getComponentByName("TextBoxHeight");
//                (*textBoxHeight)->content = "";
//                (*textBoxWidth)->content = "";
//            }
//            else
//            {
//                scenes.loadScene("Simulator");
//            }
//        }
//    }
}

void UICallback(const Unknown::UIEvent evnt)
{
    if(evnt.componentName == "ButtonStart")
    {
        Unknown::UIContainer& mainMenu = scenes.getScene<Unknown::MenuScene>()->menu;
        auto textBoxWidth = mainMenu.getComponentByName("TextBoxWidth");
        auto textBoxHeight = mainMenu.getComponentByName("TextBoxHeight");
        auto textBoxSpeed = mainMenu.getComponentByName("TextBoxSpeed");

        if ((*textBoxWidth)->content.size() > 0 && (*textBoxHeight)->content.size() > 0)
        {
            int boardWidth = std::stoi((*textBoxWidth)->content);
            int boardHeight = std::stoi((*textBoxHeight)->content);
            printf("Creating board with size %dx%d\n", boardWidth, boardHeight);
            width = boardWidth;
            height = boardHeight;
            createBoard();
            //TODO: create a resize function under unknown
            //SDL_SetWindowSize(Unknown::getUnknown()->window, width*pixelScale, height*pixelScale);
            scenes.loadScene("Simulator");
        }

        if((*textBoxSpeed)->content.size() > 0)
        {
            timer.timerSpeed = std::stoi((*textBoxSpeed)->content);
        }
    }

    if(evnt.componentName == "TextBoxWidth" || evnt.componentName == "TextBoxHeight" || evnt.componentName == "TextBoxSpeed")
    {
        if(!Unknown::isCharCodeNumber(*evnt.relatedKey))
        {
            (*evnt.relatedKey) = "";
        }
    }
}


void update()
{
    scenes.currentScene->update();
}

void updateBoardSimulation()
{
    using namespace Unknown;

    std::unique_ptr<Map> newMap = std::unique_ptr<Map>(new Map(width, height));

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
    UK_ADD_UI_LISTENER_EXTERNAL(UICallback, "mainmenu");

    font = new Unknown::Graphics::TTFont("Fonts/Arimo-Regular.ttf", 14, Unknown::Colour::BLACK);

    scenes.add(new Unknown::MenuScene("MainMenu", "MainMenuUI.json", font));
    scenes.add(new Unknown::CustomScene("Simulator", renderSimulationBoard, updateBoardSimulation));
    scenes.loadScene("MainMenu");
}


#ifdef _WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    Unknown::registerEventHandler(Unknown::ET_KEYPRESS, "mainMenu", keylistener);

	UK_UPDATE(update);
	UK_RENDER(render);

	UK_CREATE_WINDOW();

    UK_PYTHON_LOAD_SCRIPT("Test");

	init();

	UK_INIT_GAME();

	return 0;
}
