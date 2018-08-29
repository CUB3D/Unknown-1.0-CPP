#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <memory>
#include <vector>
#include "IInitable.h"
#include "Utils.h"

#include "GL/GL.h"

namespace Unknown
{
	namespace Graphics
	{
		class Image : public IInitable
		{
		    //TODO: no
		    //private:
		public:
			std::string filename;
			unsigned int textureID;

			GLuint vbo;

		public:
		    ::Unknown::Dimension<int> imageSize;

			explicit Image(const std::string& filename);
			Image& operator=(const Image& img);
			virtual ~Image();

			virtual void init() override;
			void render(const int x, const int y, const double angle, SDL_Rect* clip) const;
			void render(const int x, const int y, const double angle) const;
			void render(const int x, const int y) const;

			//virtual std::unique_ptr<Image> clone() const;
		};
	}
}

#endif
