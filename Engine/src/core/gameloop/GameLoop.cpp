//
// Created by cub3d on 17/05/2020.
//

#include "GameLoop.h"

#ifdef __EMSCRIPTEN__
#include "EmscriptenGameLoop.h"
#else
#include "PCGameLoop.h"
#endif

std::shared_ptr<GameLoop> getGameLoop() {
#ifdef __EMSCRIPTEN__
    static auto loop = std::make_shared<EmscriptenGameLoop>();
#else
    static auto loop = std::make_shared<PCGameLoop>();
#endif
    return loop;
}