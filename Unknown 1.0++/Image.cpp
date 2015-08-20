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
	if (!this->hasInit)
	{
		init();
	}

	Unknown* uk = getUnknown();

	this->textureRect.x = x;
	this->textureRect.y = y;

	SDL_RenderCopy(uk->windowRenderer, this->imageTexture, NULL, &this->textureRect);
}
