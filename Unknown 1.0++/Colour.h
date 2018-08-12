#ifndef COLOUR_H
#define COLOUR_H

#include <SDL.h>
#include <SDL_image.h>

namespace Unknown
{
	class Colour
	{
	public:
		const static Colour RED;
		const static Colour GREEN;
		const static Colour BLUE;
		const static Colour BLACK;
		const static Colour WHITE;

	    int red;
		int green;
		int blue;
		int alpha;

		Colour(const int red, const int green, const int blue, const int alpha);
		Colour(const int red, const int green, const int blue);

		Colour& operator=(const Colour& other);

		SDL_Color toSDLColour() const;


		static Colour darken(const Colour &col, const double amount);
	};

	#define UK_COLOUR_RGBA(r, g, b, a) ::Unknown::Colour(r, g, b, a)
	#define UK_COLOUR_RGB(r, g, b) ::Unknown::Colour(r, g, b)

}

#endif