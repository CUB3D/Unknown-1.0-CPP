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
#include "Scene/DebugScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Event/Event.h"
#include "Event/EventManager.h"

std::unique_ptr<Unknown::Map> map;
Unknown::Timer timer(0.2);

Unknown::SceneManager scenes;
std::shared_ptr<Unknown::Graphics::Font> font;

int width = 64;
int height = 64;
int scaleX = 0;
int scaleY = 0;

b2BodyDef testDef;
b2Body* testObj;
b2PolygonShape testShape;
b2FixtureDef testFixture;

b2BodyDef groundBody;
b2PolygonShape groundShape;
b2Body* groundBodyObj;

#define PIXEL_PER_METER 64

Unknown::Graphics::ImageSprite tmp(0, 0, UK_LOAD_IMAGE("Player.png").release());

void createBoard()
{

    groundBody.position.Set(0.0f, 25.0f);
    groundBodyObj = scenes.currentScene->world.CreateBody(&groundBody);
    groundShape.SetAsBox(50.0f, 10.0f);
    groundBodyObj->CreateFixture(&groundShape, 0);



    testDef.type = b2_dynamicBody;
    testDef.position.Set(0.0f, 3.0f);
    testObj = scenes.currentScene->world.CreateBody(&testDef);
    testShape.SetAsBox(1.0f, 1.0f);
    testFixture.shape = &testShape;
    testFixture.density = 1.0f;
    testFixture.friction = 0.3f;
    testObj->CreateFixture(&testFixture);

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

   // tmp.render();
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
            scenes.loadScene("Simulator");
            createBoard();
            //TODO: create a resize function under unknown
            //SDL_SetWindowSize(Unknown::getUnknown()->window, width*pixelScale, height*pixelScale);
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

    //TODO: way to access python vars from cpp
    tmp.location.y = testObj->GetPosition().y * PIXEL_PER_METER;
    printf("%f, %f\n", testObj->GetPosition().x, testObj->GetPosition().y);
}

void init()
{
	srand(time(NULL));
	UK_LOG_INFO_VERBOSE("This is an information log");
    UK_ADD_UI_LISTENER_EXTERNAL(UICallback, "mainmenu");

    font = std::make_shared<Unknown::Graphics::TTFont>("Fonts/Arimo-Regular.ttf", 14, Unknown::Colour::BLACK);

    scenes.add(std::make_shared<Unknown::MenuScene>("MainMenu", "MainMenuUI.json", font));
    scenes.add(std::make_shared<Unknown::CustomScene>("Simulator", renderSimulationBoard, updateBoardSimulation));
    scenes.add(std::make_shared<Unknown::DebugScene>("debug", font));
    scenes.loadScene("MainMenu");
    //scenes.loadScene("debug");
}


#ifdef _WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
    //TODO: shorthand for this
	UK_UPDATE([&] {scenes.update();});
	UK_RENDER(render);

	UK_CREATE_WINDOW();

    UK_PYTHON_LOAD_SCRIPT("Test");

	init();

	UK_INIT_GAME();

	return 0;
}
