#include "stdafx.h"
#include "Colour.h"

#include <algorithm>

Unknown::Colour::Colour(const int red, const int green, const int blue, const int alpha) : red(red), green(green), blue(blue), alpha(alpha) {}

Unknown::Colour::Colour(const int red, const int green, const int blue) : red(red), green(green), blue(blue), alpha(255) {}

SDL_Color Unknown::Colour::toSDLColour() const {
	return SDL_Color {(uint8_t) this->red, (uint8_t) this->green, (uint8_t) this->blue, (uint8_t) this->alpha};
}

Unknown::Colour& Unknown::Colour::operator=(const Colour& other) {
	this->red = other.red;
	this->green = other.green;
	this->blue = other.blue;
	this->alpha = other.alpha;

	return *this;
}

const Unknown::Colour Unknown::RED = ::Unknown::Colour(255, 0, 0);
const Unknown::Colour Unknown::GREEN = ::Unknown::Colour(0, 255, 0);
const Unknown::Colour Unknown::BLUE = ::Unknown::Colour(0, 0, 255);
const Unknown::Colour Unknown::BLACK = ::Unknown::Colour(0, 0, 0);
const Unknown::Colour Unknown::WHITE = ::Unknown::Colour(255, 255, 255);

Unknown::Colour Unknown::Colour::darken(const Colour &col, const double amount) {
    int change = 2.25 * amount;
    int r = std::max(col.red - change, 0);
    int g = std::max(col.green - change, 0);
    int b = std::max(col.blue - change, 0);
	return Colour(r, g, b, col.alpha);
}
