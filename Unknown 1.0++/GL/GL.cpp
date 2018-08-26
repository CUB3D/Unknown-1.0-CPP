//
// Created by cub3d on 25/08/18.
//

#include "GL.h"

void Unknown::initGL() {
#ifdef __EMSCRIPTEN__
    glfwInit();
#else
    gladLoadGL();
#endif
}