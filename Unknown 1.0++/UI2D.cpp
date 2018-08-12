#include "stdafx.h"
#include "UI2D.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Colour.h"
#include "Unknown.h"

void Unknown::Graphics::drawRect(const int x, const int y, const int width, const int height, const Colour colour)
{
	auto uk = getUnknown();

	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	setDrawColour(colour);

	if (SDL_RenderFillRect(uk->windowRenderer, &rect) != 0)
	{
		printf("Error: failed to draw rectangle, %s\n", SDL_GetError());
		uk->quit(ErrorCodes::SDL_RENDER_RECT_FAIL);
	}
}

void Unknown::Graphics::drawSquare(const int x, const int y, const int size, const Colour colour)
{
	drawRect(x, y, size, size, colour);
}

void Unknown::Graphics::setDrawColour(const Colour colour)
{
	auto uk = getUnknown();

	SDL_SetRenderDrawColor(uk->windowRenderer, colour.red, colour.green, colour.blue, colour.alpha);
}

void Unknown::Graphics::drawCircle(const int x, const int y, const int radius, const Colour &col) {

}
