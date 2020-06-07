//
// Created by cub3d on 14/08/18.
//

#include "StaticText.h"

Unknown::StaticText::StaticText(TTFont &font, const std::string &text, const Colour &col) {
    texture = getRendererBackend()->createFontTexture(*font.font, text.c_str(), col);
    verts = getRendererBackend()->createRectVerticies(0, 0, texture.width, texture.height);

    this->size.x = this->texture.width;
    this->size.y = this->texture.height;
}

void Unknown::StaticText::render(const int x, const int y) const {
    getRendererBackend()->renderTexture(x, y, 0, this->texture, this->verts);
}
