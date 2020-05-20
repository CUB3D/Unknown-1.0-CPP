//
// Created by cub3d on 19/05/2020.
//

#include "SDLImageManager.h"

void SDLImageManager::init() {
    #ifndef __EMSCRIPTEN__ // SDL_image isn't linked against libpng in emscripten, it uses browser decoding so init isnt needed
        int status = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);

        if (!status) {
            UK_ERROR("SDL failed to initialise PNG loading: {}", IMG_GetError());
    //                quit(ErrorCodes::SDL_WINDOW_PNG_INIT_FAIL);
        }

        UK_INFO("Loaded SDL_image");
    #else
        UK_INFO("Using emscripten, not initialsing SDL_image");
    #endif
}


