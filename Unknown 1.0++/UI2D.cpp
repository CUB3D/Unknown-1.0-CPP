#include "stdafx.h"
#include "UI2D.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Colour.h"
#include "Unknown.h"
#include "GL/glad/glad.h"
#include <cmath>

//TODO: rotation both here and for images
//TODO: refactor out sdl stuff, should have some kind of init() func that will create the screen (and make the canvas on web)
//TODO: for textures should just have a load texture that returns an id and a bind/unbind that uses that id

void Unknown::Graphics::drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour colour)
{
	auto& uk = getUnknown();

//	int startX = std::max(0, x);
//	int startY = std::max(0, y);
//	int endX = std::min(x + width, uk->screenSize->width);
//	int endY = std::min(y + height, uk->screenSize->height);
    int endX = x + width;
    int endY = y + height;


	int centerX = (x + width / 2);
	int centerY = (y + height /2);

	const double angle_ = (angle / (2.0*PI)) * 360.0;

	glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
	glTranslated(centerX, centerY, 0);
	glRotated(angle_, 0, 0, 1);
	glTranslated(-centerX, -centerY, 0);

	GL_setColour(colour);


	glBegin(GL_TRIANGLES);
	// bottom left
	glVertex3f(x, y, 0);
    glVertex3f(endX, y, 0);
    glVertex3f(x, endY, 0);

    // top left
    glVertex3f(x, endY, 0);
    glVertex3f(endX, endY, 0);
    glVertex3f(endX, y, 0);
    glEnd();

    glPopMatrix();
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
    GL_setColour(colour);

    glBegin(GL_POINTS);
    glPointSize(size);
    glVertex3f(x, y, 0);
    glEnd();
}

void Unknown::Graphics::drawCircle(const int cx, const int cy, const int radius, const Colour &col) {

    GL_setColour(col);

    int segments = 100;

    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(segments);//get the current angle

        float x = radius * cosf(theta);//calculate the x component
        float y = radius * sinf(theta);//calculate the y component

        glVertex2f(x + cx, y + cy);//output vertex

    }
    glEnd();
}

void Unknown::Graphics::drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &col) {
    GL_setColour(col);
    glBegin(GL_LINE);
    glVertex3f(sx, sy, 0);
    glVertex3f(ex, ey, 0);
    glEnd();
}

void
Unknown::Graphics::drawRect(const int x, const int y, const int width, const int height, const Colour colour) {
    drawRect(x, y, width, height, 0, colour);
}

