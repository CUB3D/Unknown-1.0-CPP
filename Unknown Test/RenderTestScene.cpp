//
// Created by cub3d on 14/08/18.
//

#include "RenderTestScene.h"
#include "UI2D.h"
#include "Font/TTFont.h"
#include "Font/StaticText.h"

Unknown::Graphics::Image img("Player.png");

std::shared_ptr<Unknown::Graphics::TTFont> font_;
std::shared_ptr<StaticText> tex;

void RenderTestScene::render() const {
    for(int i = 0; i < 80; i+=8) {
        UK_DRAW_RECT(10, 10 * i, 20, 20, UK_COLOUR_RGB(255, 0, 0));
        Unknown::Graphics::drawCircle(50, 15 * i, 10, UK_COLOUR_RGB(0, 255, 0));
        img.render(70, 10 * i);
        tex->render(150, 10*i);
    }
}

RenderTestScene::RenderTestScene() : Scene("RTest") {
    font_ = std::make_shared<Unknown::Graphics::TTFont>("Fonts/Arimo-Regular.ttf", 14, Unknown::Colour::BLUE);
    tex = std::make_shared<StaticText>(*font_, "Hello, World");
}
