//
// Created by cub3d on 14/08/18.
//

#include <SDL_types.h>
#include <SDL_surface.h>
#include "FontGlyph.h"

Unknown::Graphics::FontGlyph::FontGlyph(const char c, TTF_Font *font, const Colour &col) {
    const char str[2] = {c, '\0'};
    texture = getRendererBackend()->createFontTexture(*font, str, col);
    verts = getRendererBackend()->createRectVerticies(0, 0, texture.width, texture.height);

    this->size.width = this->texture.width;
    this->size.height = this->texture.height;
}

void Unknown::Graphics::FontGlyph::drawGlyph(const int x, const int y) const {
    getRendererBackend()->renderTexture(x, y, 0, this->texture, this->verts);
}
