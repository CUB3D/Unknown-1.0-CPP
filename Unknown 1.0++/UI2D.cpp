#include "stdafx.h"
#include "UI2D.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Colour.h"
#include "Unknown.h"

#include "GL/GL.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Graphics/RenderingBackend.h"

//TODO: rotation both here and for images
//TODO: refactor out sdl stuff, should have some kind of init() func that will create the screen (and make the canvas on web)
//TODO: for textures should just have a load texture that returns an id and a bind/unbind that uses that id

void Unknown::Graphics::drawVerticies(GLenum renderMode, const float *verticies, const int vertexCount, const double x,
                                      const double y, const double centerX, const double centerY, const double angle,
                                      const Colour &colour) {
    glEnableClientState(GL_VERTEX_ARRAY);


   //TODO: first find some replacement for glVertexPointer, its not supported by webgl and it can't be emulated
//Also I think that client states are needed for native but not for emscripten

    glVertexPointer(3, GL_FLOAT, 0, verticies);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);


    glDisableClientState(GL_VERTEX_ARRAY);

    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        printf("%d\n", err);
    }
}

void Unknown::Graphics::drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour colour)
{
    auto renderer = getRendererBackend();

    renderer->drawRect(x, y, width, height, angle, colour);

//    constexpr int VERTEX_COUNT = 18;
//
//    float verticies[VERTEX_COUNT] =  {
//        0, 0, 0,
//        (float)width, 0, 0,
//        0, (float)height, 0,
//
//        0, (float)height, 0,
//        (float)width, (float)height, 0,
//        (float)width, 0, 0
//    };
//
//    double centerX = width / 2.0;
//    double centerY = height / 2.0;
//
//    const double angle_ = (angle / (2.0*PI)) * 360.0;
//
//    drawVerticies(GL_TRIANGLES, verticies, 6, x, y, centerX, centerY, angle_, colour);
}

void Unknown::Graphics::drawSquare(const int x, const int y, const int size, const Colour colour) {
	drawRect(x, y, size, size, colour);
}

void Unknown::Graphics::drawPoint(const int x, const int y, const Colour &colour) {
    getRendererBackend()->drawPoint(x, y, colour);
}

void Unknown::Graphics::drawCircle(const int cx, const int cy, const int radius, const Colour &col) {
    getRendererBackend()->drawCircle(cx, cy, radius, col);
}

void Unknown::Graphics::drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &col) {
    getRendererBackend()->drawLine(sx, sy, ex, ey, col);
}

void Unknown::Graphics::drawRect(const int x, const int y, const int width, const int height, const Colour &colour) {
    drawRect(x, y, width, height, 0, colour);
}

