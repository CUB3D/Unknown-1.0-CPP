//
// Created by cub3d on 26/08/18.
//

#include "SDLBackend.h"

#include <SDL.h>

#include "../Unknown.h"

void Unknown::SDLBackend::drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) {
    auto& uk = getUnknown();

    SDL_SetRenderDrawColor(uk.windowRenderer, colour.red, colour.green, colour.blue, colour.alpha);

    SDL_Rect rect{x, y, width, height};

    //TODO: err handling
    SDL_RenderFillRect(uk.windowRenderer, &rect);
}
