#include "stdafx.h"
#include "Image.h"

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

#include "Unknown.h"


Unknown::Graphics::Image::Image(const char* fileName)
{
	this->texture = IMG_Load(fileName);
}

Unknown::Graphics::Image::~Image()
{
	if (this->texture)
	{
		SDL_FreeSurface(this->texture);
	}
}

void Unknown::Graphics::Image::init()
{
	Unknown* uk = getUnknown();

	if (!this->texture)
	{
		printf("Error: failed to load image, %s\n", IMG_GetError());
		uk->quit(ErrorCodes::SDL_IMAGE_LOAD_FAIL);
	}

	this->texture = SDL_ConvertSurface(this->texture, uk->windowSurface->format, NULL);

	if (!this->texture)
	{
		printf("Error: failed to convert image, %s/n", SDL_GetError());
		uk->quit(ErrorCodes::SDL_IMAGE_CONVERT_FAIL);
	}

	this->textureRect.x = 0;
	this->textureRect.y = 0;
	this->textureRect.w = this->texture->w;
	this->textureRect.h = this->texture->h;

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

	SDL_BlitSurface(this->texture, NULL, uk->windowSurface, &textureRect);
}
