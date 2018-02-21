#include "stdafx.h"
#include "Colour.h"

#include <SDL.h>
#include <SDL_image.h>
#include "Unknown.h"

Unknown::Colour::Colour(const int red, const int green, const int blue, const int alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

Unknown::Colour::Colour(const int red, const int green, const int blue) : red(red), green(green), blue(blue), alpha(255) {}

SDL_Color Unknown::Colour::toSDLColour() const
{
	//Unknown* uk = getUnknown();

	//return SDL_MapRGBA(SDL_GetWindowSurface(uk->window)->format, this->red, this->green, this->blue, this->alpha);
	return SDL_Color {(uint8_t) this->red, (uint8_t) this->green, (uint8_t) this->blue, (uint8_t) this->alpha};
}

Unknown::Colour Unknown::Colour::RED = Colour(255, 0, 0);
Unknown::Colour Unknown::Colour::GREEN = Colour(0, 255, 0);
Unknown::Colour Unknown::Colour::BLUE = Colour(0, 0, 255);
Unknown::Colour Unknown::Colour::BLACK = Colour(0, 0, 0);
Unknown::Colour Unknown::Colour::WHITE = Colour(255, 255, 255);
