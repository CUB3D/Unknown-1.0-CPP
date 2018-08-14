//
// Created by cub3d on 14/08/18.
//

#include "StaticText.h"

StaticText::StaticText(const Unknown::Graphics::TTFont &font, const std::string &text) {
    for(char c : text) {
        this->glyphs.push_back(font.getGlyph(c));
    }
}

void StaticText::render(const int x, const int y) const {
    int xPos = x;

    for(auto& glyph : glyphs) {
        glyph.drawGlyph(xPos, y);
        xPos += glyph.size.width;
    }
}
