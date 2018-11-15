#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <memory>
#include <vector>
#include "IInitable.h"

#include "GL/GL.h"
#include "Graphics/RenderingBackend.h"
#include "Graphics/Shader.h"
#include "Types/Dimension.h"

namespace Unknown
{
	namespace Graphics
	{
	    class Image : public IInitable<>
		{
		private:
			std::string filename;

			TextureInfo textureInfo;
			VertexInfo vertexInfo;
			Shader shader;


		public:
		    ::Unknown::Dimension<int> imageSize;

			explicit Image(const std::string& filename);
			Image& operator=(const Image& img);
			virtual ~Image();

			virtual void init() override;
			void render(const int x, const int y, const double angle = 0, SDL_Rect* clip = nullptr) const;
		};
	}
}

#endif
