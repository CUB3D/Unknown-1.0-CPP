#ifndef UI2D_Hrenderer
#define UI2D_H

#include "Colour.h"
#include <SDL.h>
#include <SDL_image.h>
#include "Unknown.h"

namespace Unknown
{
	namespace Graphics
	{
		void drawRect(const int x, const int y, const int width, const int height, const Colour colour);
		void drawSquare(const int x, const int y, const int size, const Colour colour);
		void drawCircle(const int x, const int y, const int radius, const Colour& col);

		void setDrawColour(const Colour colour);
	}
}

#define UK_SET_COLOUR(colour) ::Unknown::Graphics::setDrawColour(colour)
#define UK_DRAW_RECT(x, y, w, h, c) ::Unknown::Graphics::drawRect(x, y, w, h, c)
#define UK_DRAW_SQUARE(x, y, s, c) ::Unknown::Graphics::drawSquare(x, y, s, c)

#endif
