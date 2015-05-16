#ifndef COLOUR_H
#define COLOUR_H

#include <SDL.h>

namespace Unknown
{
	class Colour
	{
	private:
		int red;
		int green;
		int blue;
		int alpha;
	public:
		static Colour RED;
		static Colour GREEN;
		static Colour BLUE;

		Colour(const int red, const int green, const int blue, const int alpha);
		Colour(const int red, const int green, const int blue);

		Uint32 toSDLColour() const;
	};

	#define UK_COLOUR_RGBA(r, g, b, a) Unknown::Colour(r, g, b, a)
	#define UK_COLOUR_RGB(r, g, b) Unknown::Colour(r, g, b)

}

#endif