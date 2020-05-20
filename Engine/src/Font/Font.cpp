#include "Font.h"
#include <GL/GL.h>

#include <iostream>
#include <SDL_ttf.h>

void Unknown::Font::drawString(const std::string &string, const int x, const int y) const {
    int xPos = x;

    for(char c : string) {
        this->drawChar(c, xPos, y);

        xPos += getCharWidth(c);
    }
}

Unknown::Font::Font(const int fontSize) : fontSize(fontSize) {}

int Unknown::Font::getStringHeight(const std::string &str) const {
    return fontSize;
}
