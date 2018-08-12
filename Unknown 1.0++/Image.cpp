#include "stdafx.h"
#include "Image.h"

#include <SDL_image.h>
#include <iostream>
#include <string.h>

#include "Unknown.h"


void Unknown::Graphics::Image::init()
{
	auto uk = getUnknown();

	SDL_Surface* imageSurface = IMG_Load(this->filename.c_str());

	if (!imageSurface)
	{
		printf("Error: failed to load image, %s\n", IMG_GetError());
		uk->quit(ErrorCodes::SDL_IMAGE_LOAD_FAIL);
	}

	this->imageTexture = SDL_CreateTextureFromSurface(uk->windowRenderer, imageSurface);

	if (!imageTexture) {
		printf("Error: failed to create texture, %s\n", IMG_GetError());
		uk->quit(ErrorCodes::SDL_IMAGE_TEXTURE_CREATE_FAIL);
	}

	this->textureRect.x = 0;
	this->textureRect.y = 0;
	this->textureRect.w = imageSurface->w;
	this->textureRect.h = imageSurface->h;

	SDL_FreeSurface(imageSurface);
}

//std::unique_ptr<Unknown::Graphics::Image> Unknown::Graphics::Image::clone() const {
//	Image* clone = (Image*)malloc(sizeof(Image));
//	memcpy(clone, this, sizeof *this);
//	return std::unique_ptr<Image>(clone);
//}

void Unknown::Graphics::Image::render(const int x, const int y) const {
	this->render(x, y, 0);
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle) const {
	this->render(x, y, angle, NULL);
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle, SDL_Rect* clip) const {
    auto uk = getUnknown();

    if (!imageTexture) {
        printf("Error: failed to create texture, %s\n", IMG_GetError());
        uk->quit(ErrorCodes::SDL_IMAGE_TEXTURE_CREATE_FAIL);
    }

	auto textRect = this->textureRect;
	textRect.x = x;
	textRect.y = y;

    int status = SDL_RenderCopyEx(uk->windowRenderer, this->imageTexture, clip, &textRect, angle, NULL, SDL_FLIP_NONE);
    if(status) {
        printf("Error rendering image: %s\n", SDL_GetError());
        SDL_ClearError();
    }
}

Unknown::Graphics::Image::Image(const std::string &filename) : filename(filename), imageTexture(nullptr) {
	if(getUnknown()->currentState < UK_POST_INIT) {
	    getUnknown()->imageLateInit.push_back(this);
	} else { // There is a renderer, init now
		this->init();
	}
}

Unknown::Graphics::Image &Unknown::Graphics::Image::operator=(const Image &img) {
	this->filename = img.filename;
	this->imageTexture = nullptr;

    if(getUnknown()->currentState < UK_POST_INIT) {
        getUnknown()->imageLateInit.push_back(this);
    } else { // There is a renderer, init now
        this->init();
    }

	return *this;
}

Unknown::Graphics::Image::~Image() {
	if (this->imageTexture && getUnknown()->windowRenderer && getUnknown()->window) {
		SDL_DestroyTexture(this->imageTexture);
		this->imageTexture = NULL;
	}
}
