#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <memory>
#include <vector>

namespace Unknown
{
	namespace Graphics
	{
		class Image;
		extern std::vector<Image*> imageLateInit;

		class Image
		{
		private:
			SDL_Surface* imageSurface;
			SDL_Texture* imageTexture;

		public:
			SDL_Rect textureRect;

			Image(const std::string& filename);
			Image(const char* fileName);
			~Image();

			void init();
			void render(const int x, const int y, const double angle, SDL_Rect* clip) const;
			void render(const int x, const int y, const double angle) const;
			void render(const int x, const int y) const;

			virtual std::unique_ptr<Image> clone() const;
		};
	}
}

#endif
