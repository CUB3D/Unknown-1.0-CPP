//
// Created by cub3d on 26/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_GLBACKEND_H
#define UNKNOWN_DEVELOPMENT_TOOL_GLBACKEND_H

#include "RenderingBackend.h"
#include "FileShader.h"
#include "../GL/GL.h"
#include <map>

namespace Unknown
{
    class GLBackend : public RenderingBackend
    {
        FileShader shad;

    public:
        GLBackend();

        virtual void drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) override;
        virtual void drawPoint(const int x, const int y, const Colour& colour) override;
        virtual void drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &col) override;
        virtual void drawCircle(const int cx, const int cy, const int radius, const Colour &col) override;

        virtual TextureInfo loadTexture(std::string &path) override;
        virtual VertexInfo createRectVerticies(const int x, const int y, const int w, const int h) override;
        virtual void renderTexture(const int x, const int y, const double angle, const TextureInfo &texture, const VertexInfo &verticies)  override;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_GLBACKEND_H
