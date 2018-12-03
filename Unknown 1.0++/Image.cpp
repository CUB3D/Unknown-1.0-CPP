#include "Image.h"

#include <string.h>

#include <Unknown.h>
#include <GL/GL.h>
#include <Graphics/RenderingBackend.h>


void Unknown::Image::init() {
    this->textureInfo = getRendererBackend()->loadTexture(this->filename);

    this->imageSize.width = this->textureInfo.width;
    this->imageSize.height = this->textureInfo.height;

    this->vertexInfo = getRendererBackend()->createRectVerticies(0, 0, this->textureInfo.width, this->textureInfo.height);
}

void Unknown::Image::render(const int x, const int y, const double angle, SDL_Rect* clip) const {
    getRendererBackend()->renderTexture(x, y, angle, this->textureInfo, this->vertexInfo);
}

Unknown::Image::Image(const std::string &filename) : filename(filename) {
	if(getUnknown().currentState < UK_POST_INIT) {
	    getUnknown().lateInit.push_back(this);
	} else { // There is a renderer, init now
		this->init();
	}
}

Unknown::Image &Unknown::Image::operator=(const Image &img) {
	this->filename = img.filename;

    if(getUnknown().currentState < UK_POST_INIT) {
        getUnknown().lateInit.push_back(this);
    } else { // There is a renderer, init now
        this->init();
    }

	return *this;
}

Unknown::Image::~Image() {}

RTTR_REGISTRATION {
	rttr::registration::class_<Unknown::Image>("Image")
			.constructor<const std::string&>()
			.method("render", &Unknown::Image::render);
}
