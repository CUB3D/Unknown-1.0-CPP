//
// Created by cub3d on 26/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_GLBACKEND_H
#define UNKNOWN_DEVELOPMENT_TOOL_GLBACKEND_H

#include "RenderingBackend.h"
#include "FileShader.h"

namespace Unknown
{
    class GLBackend : public RenderingBackend
    {
        FileShader shad;

    public:
        GLBackend();

        virtual void drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) override;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_GLBACKEND_H
