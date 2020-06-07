#include "UI2D.h"

#include <Graphics/RenderingBackend.h>

void Unknown::Graphics::drawRect(const int x, const int y, const int width, const int height, const double angle, const Colour colour)
{
    getRendererBackend().drawRect(x, y, width, height, angle, colour);
}

void Unknown::Graphics::drawSquare(const int x, const int y, const int size, const Colour colour) {
	drawRect(x, y, size, size, colour);
}

void Unknown::Graphics::drawPoint(const int x, const int y, const Colour &colour) {
    getRendererBackend().drawPoint(x, y, colour);
}

void Unknown::Graphics::drawCircle(const int cx, const int cy, const int radius, const Colour &col) {
    getRendererBackend().drawCircle(cx, cy, radius, col);
}

void Unknown::Graphics::drawLine(const int sx, const int sy, const int ex, const int ey, const Colour &col) {
    getRendererBackend().drawLine(sx, sy, ex, ey, col);
}

void Unknown::Graphics::drawRect(const int x, const int y, const int width, const int height, const Colour &colour) {
    drawRect(x, y, width, height, 0, colour);
}

