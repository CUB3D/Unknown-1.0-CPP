//
// Created by cub3d on 26/08/18.
//

#include "RenderingBackend.h"
#include "SDLBackend.h"
#include "GLBackend.h"

std::shared_ptr<Unknown::RenderingBackend> Unknown::getRendererBackend() {

#ifdef __EMSCRIPTEN__
    static std::shared_ptr<RenderingBackend> backend = std::make_shared<Unknown::GLBackend>();
#else
    static std::shared_ptr<RenderingBackend> backend = std::make_shared<Unknown::GLBackend>();
#endif

    return backend;
}
