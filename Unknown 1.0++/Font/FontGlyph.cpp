//
// Created by cub3d on 14/08/18.
//

#include <SDL_types.h>
#include <SDL_surface.h>
#include "FontGlyph.h"

Unknown::Graphics::FontGlyph::FontGlyph(const char c, TTF_Font *font, const Colour &col) {
    this->texture = getRendererBackend()->

    // Draw char
    char str[2] = {c, '\0'};
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, str, col.toSDLColour());

    if(!textSurface) {
        //TODO:
    }

    // Convert to known format
    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    SDL_Surface* tmp = SDL_CreateRGBSurface(0, textSurface->w, textSurface->h, 32, rmask, gmask, bmask, amask);
    SDL_BlitSurface(textSurface, NULL, tmp, NULL);

    // Copy to gpu
    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, textSurface->w, textSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmp->pixels);

    this->size.width = textSurface->w;
    this->size.height = textSurface->h;

    SDL_FreeSurface(textSurface);
    SDL_FreeSurface(tmp);
}

void Unknown::Graphics::FontGlyph::drawGlyph(const int x, const int y) const {
    ::Unknown::getRendererBackend()->createRectVerticies(x, y, )

#ifndef __EMSCRIPTEN__

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor3f(1, 1, 1);

    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_TRIANGLES);
    // Top right
    glTexCoord2f(0, 0);
    glVertex3f(x, y, 0);
    glTexCoord2f(1, 0);
    glVertex3f(x + size.width, y, 0);
    glTexCoord2f(1, 1);
    glVertex3f(x + size.width, y + size.height, 0);

    // Bottom left
    glTexCoord2f(0, 0);
    glVertex3f(x, y, 0);
    glTexCoord2f(0, 1);
    glVertex3f(x, y + size.height, 0);
    glTexCoord2f(1, 1);
    glVertex3f(x + size.width, y + size.height, 0);

    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
#endif
}
