//
// Created by cub3d on 03/04/18.
//

#include "DebugScene.h"
#include "../UI2D.h"
#include "Types/Colour.h"

Unknown::DebugScene::DebugScene(const std::string name, std::shared_ptr<Graphics::Font> f) : MenuScene(name, "", f), font(f)
{
    //this->menu.addComponent(std::make_unique<TextBoxComponent>("maxTicks", this->font, Point<int>(0, 0), Dimension<int>(100, 30)));
}

void Unknown::DebugScene::update()
{
    MenuScene::update();
}

void Unknown::DebugScene::render() const
{
    auto& uk = getUnknown();

    UK_DRAW_RECT(0, 0, uk.screenSize->width, uk.screenSize->height, WHITE);

    std::string fps = "FPS: ";
    fps += std::to_string(uk.fps);

    printf("Test1\n");

    font->drawString(fps, uk.screenSize->width - font->getStringWidth(fps) - 10, 10);

    printf("Test2\n");

    std::string frameTime = "FrameTime: ";
    frameTime += std::to_string(uk.lastFrameTimeMS);
    font->drawString(frameTime, uk.screenSize->width - font->getStringWidth(frameTime) - 10, 30);

    std::string updateTime = "UpdateTime: ";
    updateTime += std::to_string(uk.lastUpdateTimeMS);
    font->drawString(updateTime, uk.screenSize->width - font->getStringWidth(updateTime) - 10, 50);

    MenuScene::render();
}

Unknown::DebugScene::~DebugScene()
{

}
