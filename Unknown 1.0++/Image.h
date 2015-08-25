#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>

namespace Unknown
{
	namespace Graphics
	{
		class Image
		{
		private:
			SDL_Surface* imageSurface;
			SDL_Texture* imageTexture;
			bool hasInit = false;

		public:
			SDL_Rect textureRect;

			Image(const char* fileName);
			~Image();

			void init();
			void render(const int x, const int y, const double angle);
			void render(const int x, const int y);

			virtual ::Unknown::Graphics::Image* clone() const;
		};
	}
}

#endif
