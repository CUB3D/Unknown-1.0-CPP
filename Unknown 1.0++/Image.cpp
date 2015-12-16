#include "stdafx.h"
#include "Image.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "Unknown.h"


Unknown::Graphics::Image::Image(const char* fileName)
{
	this->imageSurface = IMG_Load(fileName);
}

Unknown::Graphics::Image::~Image()
{
	if (this->imageTexture)
	{
		SDL_DestroyTexture(this->imageTexture);
		this->imageTexture = NULL;
	}
}

void Unknown::Graphics::Image::init()
{
	Unknown* uk = getUnknown();

	if (!imageSurface)
	{
		printf("Error: failed to load image, %s\n", IMG_GetError());
		uk->quit(ErrorCodes::SDL_IMAGE_LOAD_FAIL);
	}

	this->imageTexture = SDL_CreateTextureFromSurface(uk->windowRenderer, this->imageSurface);

	if (!imageTexture)
	{
		printf("Error: failed to create texture, %s\n", IMG_GetError());
		uk->quit(ErrorCodes::SDL_IMAGE_TEXTURE_CREATE_FAIL);
	}

	this->textureRect.x = 0;
	this->textureRect.y = 0;
	this->textureRect.w = this->imageSurface->w;
	this->textureRect.h = this->imageSurface->h;

	SDL_FreeSurface(this->imageSurface);
	this->imageSurface = NULL;

	this->hasInit = true;
}

void Unknown::Graphics::Image::render(const int x, const int y)
{
	this->render(x, y, 0);
}

Unknown::Graphics::Image* Unknown::Graphics::Image::clone() const
{
	Image* clone = (Image*)malloc(sizeof Image);
	memcpy(clone, this, sizeof *this);
	return clone;
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle)
{
	this->render(x, y, angle, NULL);
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle, SDL_Rect* clip)
{
	if (!this->hasInit)
	{
		init();
	}

	Unknown* uk = getUnknown();

	this->textureRect.x = x;
	this->textureRect.y = y;

	SDL_RenderCopyEx(uk->windowRenderer, this->imageTexture, clip, &this->textureRect, angle, NULL, SDL_FLIP_NONE);
}
