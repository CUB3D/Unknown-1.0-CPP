//
// Created by cub3d on 26/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SDLBACKEND_H
#define UNKNOWN_DEVELOPMENT_TOOL_SDLBACKEND_H

#include "../Colour.h"
#include "RenderingBackend.h"


namespace Unknown
{
    class SDLBackend : public RenderingBackend {
    public:
        virtual void drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) override;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_SDLBACKEND_H
