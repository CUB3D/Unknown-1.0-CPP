//
// Created by cub3d on 14/08/18.
//

#include "BitmapFont.h"

void Unknown::Graphics::BitmapFont::drawChar(const char character, const int x, const int y) const
{
    int position = layout.find(character);

    SDL_Rect clip;
    clip.x = position * this->fontSize;
    clip.y = 0;
    clip.w = this->fontSize;
    clip.h = this->fontSize;

    this->fontSheet.render(x, y, 0, &clip);
}

int Unknown::Graphics::BitmapFont::getStringWidth(const std::string &str) const
{
    return str.size() * fontSize;
}

Unknown::Graphics::BitmapFont::BitmapFont(Image img, const std::string &layout, const int fontSize) : Font(fontSize), fontSheet(img), layout(layout) {}

void Unknown::Graphics::BitmapFont::init() {} // Could gen a cache here
