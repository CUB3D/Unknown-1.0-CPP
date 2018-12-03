#include "Image.h"

#include <string.h>

#include <Unknown.h>
#include <GL/GL.h>
#include <Graphics/RenderingBackend.h>


void Unknown::Graphics::Image::init() {
    this->textureInfo = getRendererBackend()->loadTexture(this->filename);

    this->imageSize.width = this->textureInfo.width;
    this->imageSize.height = this->textureInfo.height;

    this->vertexInfo = getRendererBackend()->createRectVerticies(0, 0, this->textureInfo.width, this->textureInfo.height);
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle, SDL_Rect* clip) const {
    getRendererBackend()->renderTexture(x, y, angle, this->textureInfo, this->vertexInfo);
}

Unknown::Graphics::Image::Image(const std::string &filename) : filename(filename) {
	if(getUnknown().currentState < UK_POST_INIT) {
	    getUnknown().lateInit.push_back(this);
	} else { // There is a renderer, init now
		this->init();
	}
}

Unknown::Graphics::Image &Unknown::Graphics::Image::operator=(const Image &img) {
	this->filename = img.filename;

    if(getUnknown().currentState < UK_POST_INIT) {
        getUnknown().lateInit.push_back(this);
    } else { // There is a renderer, init now
        this->init();
    }

	return *this;
}

const Unknown::TextureInfo& Unknown::Graphics::Image::getTextureInfo() const {
    return this->textureInfo;
}

void Unknown::Graphics::Image::setDimentions(Dimension<int>& dimension) {
    this->imageSize = dimension;
    // TODO: destroy old verticies
    this->vertexInfo = getRendererBackend()->createRectVerticies(0, 0, dimension.width, dimension.height);
}

Unknown::Graphics::Image::~Image() {}

RTTR_REGISTRATION {
	rttr::registration::class_<Unknown::Graphics::Image>("Image")
			.constructor<const std::string&>()
			.method("render", &Unknown::Graphics::Image::render);
}
