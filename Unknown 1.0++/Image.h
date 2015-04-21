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
			SDL_Rect textureRect;
			bool hasInit = false;

		public:
			Image(const char* fileName);
			~Image();

			void init();
			void render(const int x, const int y);
		};
	}
}

#endif
