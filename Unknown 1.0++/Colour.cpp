#include "stdafx.h"
#include "Colour.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Unknown.h"

Unknown::Colour::Colour(const int red, const int green, const int blue, const int alpha)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

Unknown::Colour::Colour(const int red, const int green, const int blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = 255;
}

Uint32 Unknown::Colour::toSDLColour() const
{
	Unknown* uk = getUnknown();

	return SDL_MapRGBA(SDL_GetWindowSurface(uk->window)->format, this->red, this->green, this->blue, this->alpha);
}

Unknown::Colour Unknown::Colour::RED = Colour(255, 0, 0);
Unknown::Colour Unknown::Colour::GREEN = Colour(0, 255, 0);
Unknown::Colour Unknown::Colour::BLUE = Colour(0, 0, 255);
