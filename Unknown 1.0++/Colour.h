#ifndef COLOUR_H
#define COLOUR_H

#include <SDL.h>
#include <SDL_image.h>

namespace Unknown
{
	class Colour
	{
	public:
		static Colour RED;
		static Colour GREEN;
		static Colour BLUE;
		static Colour BLACK;
		static Colour WHITE;

		const int red;
		const int green;
		const int blue;
		const int alpha;

		Colour(const int red, const int green, const int blue, const int alpha);
		Colour(const int red, const int green, const int blue);

		SDL_Color toSDLColour() const;
	};

	#define UK_COLOUR_RGBA(r, g, b, a) Unknown::Colour(r, g, b, a)
	#define UK_COLOUR_RGB(r, g, b) Unknown::Colour(r, g, b)

}

#endif