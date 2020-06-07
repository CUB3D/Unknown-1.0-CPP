//
// Created by cub3d on 26/08/18.
//

#include "RenderingBackend.h"
#include "SDLBackend.h"
#include "GLBackend.h"
#include <Tracy.hpp>

Unknown::RenderingBackend& Unknown::getRendererBackend() {
    ZoneScopedN("UK::getRendererBackend");

    switch(getUnknown().config.rendererMode) {
        case 0: {
            static auto backend = ::Unknown::GLBackend {};
            return backend;
        }
        case 1: {
            static auto backend = ::Unknown::SDLBackend {};
            return backend;
        }
    }
}

Unknown::VertexInfo::VertexInfo() : vao(0), vbo(0), bounds({0, 0, 0, 0}), vertexCount(0) {}
