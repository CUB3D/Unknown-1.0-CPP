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

