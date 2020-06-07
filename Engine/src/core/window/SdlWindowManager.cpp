//
// Created by cub3d on 19/05/2020.
//

#include <SDL.h>
#include "SdlWindowManager.h"
#include "core/log/Log.h"


void SDLWindowManager::init(int width, int height) {
    this->screenSize = glm::vec2(width, height);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        UK_ERROR("SDL failed to initialise: {}", SDL_GetError());
//        quit(ErrorCodes::SDL_INITIALIZATION_FAIL);
    }

//    if(config.MSAA) {
        // Enable MSAA
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
//    }

    // Vsync
//    SDL_GL_SetSwapInterval(config.vsync ? 1 : 0);
    SDL_GL_SetSwapInterval(0);

//    UK_INFO(config.vsync ? "Enabled vsync" : "Disabled vsync");

    this->window = SDL_CreateWindow("Unknown", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

    if (!window) {
        UK_ERROR("SDL failed to create window: {}", SDL_GetError());
//        quit(ErrorCodes::SDL_WINDOW_CREATION_FAIL);
    }

    this->windowRenderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (!windowRenderer) {
        UK_ERROR("SDL failed to create renderer: {}", SDL_GetError());
//        quit(ErrorCodes::SDL_WINDOW_RENDERER_CREATION_FAIL);
    }
}
