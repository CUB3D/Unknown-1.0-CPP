//
// Created by cub3d on 17/05/2020.
//

#include "EmscriptenGameLoop.h"
#ifdef __EMSCRIPTEN__

void EmscriptenGameLoop::init() {
    emscripten_set_main_loop(loop(), 0, 1);
}

#endif
