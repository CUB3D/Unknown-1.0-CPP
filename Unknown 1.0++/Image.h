#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <memory>
#include <vector>

namespace Unknown
{
	namespace Graphics
	{
		class Image
		{
		private:
			std::string filename;

			std::shared_ptr<SDL_Texture> imageTexture;

		public:
			SDL_Rect textureRect;

			Image(const std::string& filename);
			Image& operator=(const Image& img);
			virtual ~Image() = default;

			void init();
			void render(const int x, const int y, const double angle, SDL_Rect* clip) const;
			void render(const int x, const int y, const double angle) const;
			void render(const int x, const int y) const;

			virtual std::unique_ptr<Image> clone() const;
		};
	}
}

#endif
