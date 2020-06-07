//
// Created by cub3d on 14/08/18.
//

#include <SDL_types.h>
#include <SDL_surface.h>
#include "FontGlyph.h"

Unknown::FontGlyph::FontGlyph(const char c, TTF_Font *font, const Colour &col) {
    const char str[2] = {c, '\0'};
    texture = getRendererBackend()->createFontTexture(*font, str, col);
    verts = getRendererBackend()->createRectVerticies(0, 0, texture.width, texture.height);

    this->size.x = this->texture.width;
    this->size.y = this->texture.height;
}

void Unknown::FontGlyph::drawGlyph(const int x, const int y) const {
    getRendererBackend()->renderTexture(x, y, 0, this->texture, this->verts);
}
