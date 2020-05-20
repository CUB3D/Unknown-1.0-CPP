//
// Created by cub3d on 19/05/2020.
//

#include <SDL_ttf.h>
#include "FontManager.h"
#include "core/log/Log.h"

void FontManager::init() {
    if(TTF_Init() == -1) {
        UK_ERROR("SDL failed to initialise TTF handling: {}", TTF_GetError());
//        quit(ErrorCodes::SDL_WINDOW_TTF_INIT_FAIL);
    }
}
