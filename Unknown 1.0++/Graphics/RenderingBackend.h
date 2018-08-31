//
// Created by cub3d on 26/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_RENDERINGBACKEND_H
#define UNKNOWN_DEVELOPMENT_TOOL_RENDERINGBACKEND_H


#include "../Colour.h"
#include <memory>
#include <map>
#include <vector>
#include "../GL/GL.h"

namespace Unknown
{
    //TODO: should there be a seperate gluint and SDL_Texture
    struct TextureInfo {
        int width;
        int height;
        unsigned long long int pointer;
    };

    class VertexInfo {
    public:
        GLuint vbo;
        GLuint vao;
        SDL_Rect bounds;

        VertexInfo();
    };

    class RenderingBackend
    {
    protected:
        std::map<std::string, TextureInfo> textureMap;
        std::vector<VertexInfo> vertexLookup;

    public:
        virtual void drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) = 0;
        virtual void drawPoint(const int x, const int y, const Colour& colour) = 0;
        virtual void drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &col) = 0;
        virtual void drawCircle(const int cx, const int cy, const int radius, const Colour &col) = 0;

        virtual TextureInfo loadTexture(std::string &path) = 0;
        virtual VertexInfo createRectVerticies(const int x, const int y, const int w, const int h) = 0;
        virtual void renderTexture(const int x, const int y, const double angle, const TextureInfo &texture, const VertexInfo &verticies) = 0;
    };

    std::shared_ptr<RenderingBackend> getRendererBackend();
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_RENDERINGBACKEND_H
