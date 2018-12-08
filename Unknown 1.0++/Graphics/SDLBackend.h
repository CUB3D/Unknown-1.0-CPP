//
// Created by cub3d on 26/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_SDLBACKEND_H
#define UNKNOWN_DEVELOPMENT_TOOL_SDLBACKEND_H

#include "Types/Colour.h"
#include "RenderingBackend.h"
#include "../Unknown.h"


namespace Unknown
{
    class SDLBackend : public RenderingBackend {
    public:
        virtual void intialise(const EngineConfig& config) override;
        virtual void createContext(SDL_Window *window) override;
        virtual void quit() override;

        void setColour(Unknown &uk, const Colour &colour);

        virtual void drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour &colour) override;
        virtual void drawPoint(const int x, const int y, const Colour& colour) override;
        virtual void drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &col) override;
        virtual void drawCircle(const int cx, const int cy, const int radius, const Colour &col) override;

        virtual TextureInfo loadTexture(const std::string &path) override;
        virtual VertexInfo createRectVerticies(const float x, const float y, const float w, const float h) override;
        virtual void renderTexture(const int x, const int y, const double angle, const TextureInfo &texture,
                                   const VertexInfo &verticies,
                                   const Dimension<float> renderSize) override;

        virtual void clearScreen() override;

        TextureInfo createFontTexture(TTF_Font &font, const char *str, const Colour &col) override;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_SDLBACKEND_H
