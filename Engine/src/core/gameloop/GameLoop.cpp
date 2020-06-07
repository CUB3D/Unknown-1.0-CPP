//
// Created by cub3d on 17/05/2020.
//

#include "GameLoop.h"

#ifdef __EMSCRIPTEN__
#include "EmscriptenGameLoop.h"
#else
#include "PCGameLoop.h"
#endif

GameLoop& getGameLoop() {
#ifdef __EMSCRIPTEN__
    static auto l = EmscriptenGameLoop {};
#else
    static auto l = PCGameLoop {};
#endif
    return l;
}


GameLoop& mainGameLoop = getGameLoop();
