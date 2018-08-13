#include "stdafx.h"
#include "UI2D.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Colour.h"
#include "Unknown.h"

void Unknown::Graphics::drawRect(const int x, const int y, const int width, const int height, const Colour colour)
{
	auto& uk = getUnknown();

	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = width;
	rect.h = height;

	setDrawColour(colour);

	if (SDL_RenderFillRect(uk.windowRenderer, &rect) != 0)
	{
		printf("Error: failed to draw rectangle, %s\n", SDL_GetError());
		uk.quit(ErrorCodes::SDL_RENDER_RECT_FAIL);
	}
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

void Unknown::Graphics::drawCircle(const int x, const int y, const int radius, const Colour &col) {
	setDrawColour(col);

	int segments = 100;

	SDL_Point points[100];

	for(int ii = 0; ii < segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(segments);//get the current angle

		float dx = radius * cosf(theta);//calculate the x component
		float dy = radius * sinf(theta);//calculate the y component

		points[ii].x = x + dx;
		points[ii].y = y + dy;
	}

	SDL_RenderDrawLines(getUnknown().windowRenderer, points, segments);
}

void Unknown::Graphics::drawLine(int sx, int sy, int ex, int ey, const Colour &col) {
	auto& uk = getUnknown();

	setDrawColour(col);
	SDL_RenderDrawLine(uk.windowRenderer, sx, sy, ex, ey);
}
