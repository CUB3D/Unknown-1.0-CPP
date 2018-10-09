//
// Created by cub3d on 25/08/18.
//

#include "GL.h"
#include "../Utils.h"

void Unknown::initGL() {
#ifdef __EMSCRIPTEN__
    glfwInit();
#else
    gladLoadGL();
#endif
}

glm::mat4 Unknown::glmhPerspectivef2(float fovyInDegrees, float aspectRatio, float znear, float zfar) {
    float ymax, xmax;
    ymax = znear * tanf(fovyInDegrees * PI / 360.0);
    xmax = ymax * aspectRatio;
    return glm::frustum(-xmax, xmax, -ymax, ymax, znear, zfar);
}