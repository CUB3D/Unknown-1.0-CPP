//
// Created by cub3d on 14/08/18.
//

#include "TTFont.h"
#include "Font.h"

#include "../GL/GL.h"

Unknown::Graphics::TTFont::TTFont(const std::string &name, const int size, const Colour &colour) : Font(size), path(name), fontSize(size), colour(colour) {
    if(getUnknown().currentState < UK_POST_INIT) {
        getUnknown().lateInit.push_back(this);
    } else { // There is a renderer, init now
        this->init();
    }
}

void Unknown::Graphics::TTFont::drawString(const std::string &string, const int x, const int y) const
{
    int xPos = x;

    for(char c : string) {
        drawChar(c, xPos, y);

        xPos += getCharWidth(c);
    }
}

int Unknown::Graphics::TTFont::getStringWidth(const std::string &str) const
{
    int width = 0;
    TTF_SizeText(this->font, str.c_str(), &width, NULL);
    return width;
}

int Unknown::Graphics::TTFont::getStringHeight(const std::string &str) const
{
    int height = 0;
    TTF_SizeText(this->font, str.c_str(), NULL, &height);
    return height;
}

void Unknown::Graphics::TTFont::drawChar(const char c, const int x, const int y) const {
    auto glyph = glyphMap.find(c);

    if(glyph != glyphMap.end()) {
        glyph->second.drawGlyph(x, y);
    } else {
        printf("Error no glyph %c for font %s\n", c, path.c_str());
    }

}

int Unknown::Graphics::TTFont::getCharWidth(const char c) const {
    int w;
    char fnt[2] = {c, '\0'};
    TTF_SizeText(this->font, fnt, &w, nullptr);
    return w;
}

void Unknown::Graphics::TTFont::init() {
    this->font = TTF_OpenFont(path.c_str(), fontSize);

    if(!this->font) {
        printf("Error [Font]: %s\n", TTF_GetError());
    }


    std::string s = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890>?./@~'#{}[]:!\"£$%^&*()#\\|`¬ ,";
    for(char c : s) {
        glyphMap.insert(std::make_pair(c, FontGlyph(c, this->font, this->colour)));
    }
}

Unknown::Graphics::FontGlyph Unknown::Graphics::TTFont::getGlyph(const char c) const {
    auto glyph = glyphMap.find(c);
    if(glyph != glyphMap.end())
        return glyph->second;
}
