// Unknown Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include "Colour.h"
#include "Map.h"
#include "Image.h"
#include "Input.h"
#include "Loader.h"
#include "Animation.h"
#include "Font/Font.h"
#include "Particle.h"
#include "UI.h"
#include "UI2D.h"
#include "Unknown.h"
#include "Log.h"
#include "Timer.h"

#include <cmath>
#include <memory>
#include "Scene/DebugScene.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Event/Event.h"
#include "Event/EventManager.h"
#include <SDL_mixer.h>
#include <Renderer/BasicTileMapRenderer.h>
#include <Editor/EditorBase.h>
#include "Map/BinaryMapGenerator.h"

#include "PhysicsTestScene.h"
#include "RenderTestScene.h"

//Unknown::Map map(1, 1);
//Unknown::Timer timer(0.2f);
//
//std::shared_ptr<Unknown::Graphics::Font> font;
//
//int width = 64;
//int height = 64;
//int scaleX = 0;
//int scaleY = 0;
//
//#define PIXEL_PER_METER 64
//
////Unknown::Graphics::ImageSprite tmp(0, 0, nullptr);
////std::shared_ptr<Unknown::BasicTileMapRenderer> boardRenderer;
//
//void renderTile(int, int, int, int);
//
//void createBoard()
//{
//    map = Unknown::Map(width, height);
//
//    Unknown::BinaryMapGenerator().generate(map);
//
//    //boardRenderer = std::make_shared<Unknown::BasicTileMapRenderer>(map, renderTile, false);
//    //Unknown::getUnknown().globalSceneManager.getScene<Unknown::CustomScene>()->renderables.push_back(static_cast<std::shared_ptr<Unknown::IRenderable>>(boardRenderer));
//
//    auto& uk = Unknown::getUnknown();
//    scaleX = uk.screenSize->width / width;
//    scaleY = uk.screenSize->height / height;
//
//    printf("Board creation complete\n");
//}
//
//Unknown::Colour colours[2] = {Unknown::Colour::WHITE, Unknown::Colour::BLACK};
//
//void renderTile(int x, int y, int id, int data) {
//    UK_DRAW_RECT(x * scaleX, y * scaleY, scaleX, scaleY, colours[id]);
//}
//
//int checkTile(int x, int y, Unknown::Map& map)
//{
//    return map.isOnBoard(x,y) ? map(x,y) : 0;
//}
//
//void UICallback(std::shared_ptr<Unknown::UIEvent> evnt)
//{
//    if(evnt->componentName == "ButtonStart")
//    {
//        Unknown::UIContainer& mainMenu = Unknown::getUnknown().globalSceneManager.getScene<Unknown::MenuScene>()->menu;
//        std::string widthText = mainMenu.getComponentValue("TextBoxWidth");
//        std::string heightText = mainMenu.getComponentValue("TextBoxHeight");
//        std::string speedText = mainMenu.getComponentValue("TextBoxSpeed");
//
//        int boardWidth = 0;
//        int boardHeight = 0;
//        int speed = 0;
//
//        if(Unknown::stringToInt(widthText, boardWidth) && Unknown::stringToInt(heightText, boardHeight)) {
//            printf("Creating board with size %dx%d\n", boardWidth, boardHeight);
//            width = boardWidth;
//            height = boardHeight;
//            UK_LOAD_SCENE("Simulator");
//            createBoard();
//            //TODO: create a resize function under unknown
//            //SDL_SetWindowSize(Unknown::getUnknown()->window, width*pixelScale, height*pixelScale);
//        }
//
//        if(Unknown::stringToInt(speedText, speed))
//        {
//            timer.timerSpeed = speed;
//        }
//    }
//}
//
//void onResize(Unknown::Event& evt) {
//    if(Unknown::getUnknown().globalSceneManager.currentSceneName == "Simulator") {
//        auto& uk = Unknown::getUnknown();
//        scaleX = uk.screenSize->width / width;
//        scaleY = uk.screenSize->height / height;
//    } else {
//        auto menu = dynamic_cast<Unknown::MenuScene*>(Unknown::getUnknown().globalSceneManager.currentScene.get());
//        if(menu) {
//            menu->reloadMenu();
//        }
//    }
//}
//
//void updateBoardSimulation()
//{
//    using namespace Unknown;
//
//    Map newMap = Map(width, height);
//
//    if (timer.isTickComplete())
//    {
//        for (int x = 0; x <  map.mapSize.width; x++)
//        {
//            for (int y = 0; y <  map.mapSize.height; y++)
//            {
//                int alive = map.getTileID(x, y);
//                int popcount = 0;
//                popcount += checkTile(x - 1, y - 1, map);
//                popcount += checkTile(x - 1, y, map);
//                popcount += checkTile(x - 1, y + 1, map);
//
//                popcount += checkTile(x, y - 1, map);
//                popcount += checkTile(x, y + 1, map);
//
//                popcount += checkTile(x + 1, y - 1, map);
//                popcount += checkTile(x + 1, y, map);
//                popcount += checkTile(x + 1, y + 1, map);
//
//                if (alive)
//                {
//                    newMap(x, y) = !(popcount < 2 || popcount > 3);
//                } else {
//                    newMap(x, y) = (popcount == 3);
//                }
//            }
//        }
//
//        map = newMap;
//    }
//}

void init()
{
//    UK_ADD_UI_LISTENER_EXTERNAL(UICallback, "mainmenu");
//
//    Unknown::registerEventHandler(Unknown::ET_WINDOW_RESIZE, "onResize", onResize);
//
//	tmp.image = new Unknown::Graphics::Image("Player.png");
//
//    font = std::make_shared<Unknown::Graphics::TTFont>("Fonts/Arimo-Regular.ttf", 14, Unknown::Colour::BLACK);

    UK_ADD_SCENE(std::make_shared<RenderTestScene>());
    //UK_ADD_SCENE(std::make_shared<Unknown::MenuScene>("MainMenu", "MainMenuUI.json", font));
    //UK_ADD_SCENE(std::make_shared<Unknown::CustomScene>("Simulator", nullptr, updateBoardSimulation));
    //UK_ADD_SCENE(std::make_shared<Unknown::DebugScene>("debug", font));
    //UK_ADD_SCENE(std::make_shared<PhysicsTestScene>());
    UK_ADD_SCENE(std::make_shared<Unknown::EditorBase>("Phys"));
    //UK_LOAD_SCENE("MainMenu");
   // UK_LOAD_SCENE("Phys");
    UK_LOAD_SCENE("RTest");
    //UK_LOAD_SCENE("Editor");
}


#ifdef _WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	//UK_CREATE_WINDOW();
	::Unknown::getUnknown().createWindow("Test", 1024, 1024, 60);

	init();

	UK_INIT_GAME();

	return 0;
}
