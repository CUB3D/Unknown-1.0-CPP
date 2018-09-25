#ifndef UI2D_H
#define UI2D_H

#include "Colour.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Unknown.h"

namespace Unknown
{
	namespace Graphics
	{
		void drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour colour);
		void drawRect(const int x, const int y, const int width, const int height, const Colour &colour);
		void drawSquare(const int x, const int y, const int size, const Colour colour);
		void drawPoint(const int x, const int y, const Colour& colour);
		void drawCircle(const int cx, const int cy, const int radius, const Colour& col);
		void drawLine(const int sx, const int sy, const int ex, const int ey, const Colour& col);

//		//TODO: merge these
//		void GL_setColour(const Colour& colour);
//		void setDrawColour(const Colour colour);
	}
}

//#define UK_SET_COLOUR(colour) ::Unknown::Graphics::setDrawColour(colour)
#define UK_DRAW_RECT(x, y, w, h, a, ...) ::Unknown::Graphics::drawRect(x, y, w, h, a, ##__VA_ARGS__)
#define UK_DRAW_SQUARE(x, y, s, c) ::Unknown::Graphics::drawSquare(x, y, s, c)

#endif
