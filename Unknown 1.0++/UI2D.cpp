#include "stdafx.h"
#include "UI2D.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Colour.h"
#include "Unknown.h"

#include "GL/GL.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

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
    constexpr int VERTEX_COUNT = 18;

    float verticies[VERTEX_COUNT] =  {
        0, 0, 0,
        (float)width, 0, 0,
        0, (float)height, 0,

        0, (float)height, 0,
        (float)width, (float)height, 0,
        (float)width, 0, 0
    };

    double centerX = width / 2.0;
    double centerY = height / 2.0;

    const double angle_ = (angle / (2.0*PI)) * 360.0;

    drawVerticies(GL_TRIANGLES, verticies, 6, x, y, centerX, centerY, angle_, colour);
}

void Unknown::Graphics::drawSquare(const int x, const int y, const int size, const Colour colour)
{
	drawRect(x, y, size, size, colour);
}

void Unknown::Graphics::setDrawColour(const Colour colour)
{
	auto& uk = getUnknown();

	SDL_SetRenderDrawColor(uk.windowRenderer, colour.red, colour.green, colour.blue, colour.alpha);
}

void Unknown::Graphics::GL_setColour(const Colour &colour) {
    glColor4f((float) colour.red / 255.0, (float) colour.green / 255.0, (float) colour.blue / 255.0, (float) colour.alpha / 255.0);
}

void Unknown::Graphics::drawPoint(const int x, const int y, const int size, const Colour &colour) {
    constexpr int vertexCount = 1;
    float verticies[vertexCount * 3] = {
        (float) x, (float) y, 0
    };

    drawVerticies(GL_POINTS, verticies, vertexCount, 0, 0, 0, 0, 0, colour);
}

void Unknown::Graphics::drawCircle(const int cx, const int cy, const int radius, const Colour &col) {

    int vertexCount = 100;
    //float verticies[vertexCount * 3];

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

    GL_setColour(col);

//    for(int i = 0; i < vertexCount; i++) {
//        float theta = 2.0f * 3.1415926f * float(i) / float(vertexCount);//get the current angle
//
//        float x = radius * cosf(theta);//calculate the x component
//        float y = radius * sinf(theta);//calculate the y component
//
//        verticies[3 * i] = x;
//        verticies[3 * i + 1] = y;
//        verticies[3 * i + 2] = 0;
//    }


    float theta = 2 * 3.1415926 / float(vertexCount);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = radius;
    float y = 0;

    glBegin(GL_POLYGON);
    for(int ii = 0; ii < vertexCount; ii++)
    {
       glVertex3f(x + cx, y + cy, 0);

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();

    //drawVerticies(GL_LINE_LOOP, verticies, vertexCount, cx, cy, 0, 0, 0, col);
}

void Unknown::Graphics::drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &col) {
    //TODO: fix
    constexpr int vertexCount = 2;
    float verticies[vertexCount * 3] = {
        (float) sx, (float) sy, 0,
        (float) ex, (float) ey, 0
    };

    drawVerticies(GL_LINES, verticies, vertexCount, 0, 0, 0, 0, 0, col);
}

void Unknown::Graphics::drawRect(const int x, const int y, const int width, const int height, const Colour &colour) {
    drawRect(x, y, width, height, 0, colour);
}

