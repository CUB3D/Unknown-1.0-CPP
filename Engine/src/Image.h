#ifndef IMAGE_H
#define IMAGE_H

#include <SDL.h>
#include <memory>
#include <vector>

#include "GL/GL.h"
#include "Graphics/RenderingBackend.h"

namespace Unknown
{
	class Image
	{
	private:
		std::string filename;

		TextureInfo textureInfo;
		VertexInfo vertexInfo;


	public:
	    glm::vec2 imageSize;
		glm::vec2 renderScale;


		explicit Image(const std::string& filename);
		Image& operator=(const Image& img);

		virtual const TextureInfo& getTextureInfo() const;
		virtual const VertexInfo& getVertexInfo() const;
		virtual void setDimentions(glm::vec2& dimension);

		virtual void init();
		void render(const int x, const int y, const double angle = 0, SDL_Rect* clip = nullptr) const;
	};
}

#endif
