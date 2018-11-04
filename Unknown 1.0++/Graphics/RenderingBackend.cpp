//
// Created by cub3d on 26/08/18.
//

#include "RenderingBackend.h"
#include "SDLBackend.h"
#include "GLBackend.h"

std::shared_ptr<Unknown::RenderingBackend> Unknown::getRendererBackend() {

    switch(getUnknown().config.rendererMode) {
        case 0: {
            static std::shared_ptr<RenderingBackend> backend = std::make_shared<::Unknown::GLBackend>();
            return backend;
        }
        case 1: {
            static std::shared_ptr<RenderingBackend> backend = std::make_shared<::Unknown::SDLBackend>();
            return backend;
        }
        default: {
            printf("Error: Unknown backend\n");
            return nullptr;
        }
    }
//
//#ifdef __EMSCRIPTEN__
//    //SDL
//    static std::shared_ptr<RenderingBackend> backend = std::make_shared<::Unknown::GLBackend>();
//#else
//    static std::shared_ptr<RenderingBackend> backend = std::make_shared<::Unknown::GLBackend>();
//#endif
//
//    return backend;
}

Unknown::VertexInfo::VertexInfo() : vao(0), vbo(0), bounds({0, 0, 0, 0}) {}
