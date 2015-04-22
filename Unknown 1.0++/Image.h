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
			SDL_Surface* texture;
			bool hasInit = false;

		public:
			SDL_Rect textureRect;

			Image(const char* fileName);
			~Image();

			void init();
			void render(const int x, const int y);
		};
	}
}

#endif
