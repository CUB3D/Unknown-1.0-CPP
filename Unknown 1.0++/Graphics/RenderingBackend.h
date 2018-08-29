//
// Created by cub3d on 26/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_RENDERINGBACKEND_H
#define UNKNOWN_DEVELOPMENT_TOOL_RENDERINGBACKEND_H


#include "../Colour.h"
#include <memory>

namespace Unknown
{
    class RenderingBackend
    {
    public:
        virtual void drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) = 0;
    };

    std::shared_ptr<RenderingBackend> getRendererBackend();
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_RENDERINGBACKEND_H
