#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <memory>
#include <vector>
#include "Utils.h"

namespace Unknown
{
	namespace Graphics
	{
		class Image
		{
		private:
			std::string filename;
			SDL_Texture* imageTexture;

		public:
		    ::Unknown::Dimension<int> imageSize;

			explicit Image(const std::string& filename);
			Image& operator=(const Image& img);
			virtual ~Image();

			void init();
			void render(const int x, const int y, const double angle, SDL_Rect* clip) const;
			void render(const int x, const int y, const double angle) const;
			void render(const int x, const int y) const;

			//virtual std::unique_ptr<Image> clone() const;
		};
	}
}

#endif
