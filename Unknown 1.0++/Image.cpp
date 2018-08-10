#include "stdafx.h"
#include "Image.h"

#include <SDL_image.h>
#include <iostream>
#include <string.h>

#include "Unknown.h"
#include "GL/glad/glad.h"

std::vector<Unknown::Graphics::Image*> Unknown::Graphics::imageLateInit;

Unknown::Graphics::Image::Image(const char* fileName)
{
	this->imageSurface = IMG_Load(fileName);

    if(!this->imageSurface) {
        printf("Error: Failed to initiate image: %s\n", SDL_GetError());
        getUnknown()->quit(ErrorCodes::SDL_IMAGE_LOAD_FAIL);
    }

    if(getUnknown()->currentState < UK_POST_INIT) {
        imageLateInit.push_back(this);
    } else { // There is a renderer, init now
        this->init();
    }
}

Unknown::Graphics::Image::~Image()
{
	if (this->imageTexture && getUnknown()->windowRenderer && getUnknown()->window)
	{
		SDL_DestroyTexture(this->imageTexture);
		this->imageTexture = NULL;
	}
}

void Unknown::Graphics::Image::init()
{
	auto uk = getUnknown();

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
}

std::unique_ptr<Unknown::Graphics::Image> Unknown::Graphics::Image::clone() const {
	Image* clone = (Image*)malloc(sizeof(Image));
	memcpy(clone, this, sizeof *this);
	return std::unique_ptr<Image>(clone);
}

void Unknown::Graphics::Image::render(const int x, const int y) const {
	this->render(x, y, 0);
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle) const {
	this->render(x, y, angle, NULL);
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle, SDL_Rect* clip) const {
	auto uk = getUnknown();

	auto textRect = this->textureRect;
	textRect.x = x;
	textRect.y = y;

	SDL_GL_BindTexture(this->imageTexture, 0, 0);

    int centerX = (x + textRect.w / 2);
    int centerY = (y + textRect.h /2);

    //const double angle_ = (angle / (2.0*PI)) * 360.0;

    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glTranslated(centerX, centerY, 0);
    glRotated(angle, 0, 0, 1);
    glTranslated(-centerX, -centerY, 0);


    glColor3f(1, 1, 1);

    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_TRIANGLES);
    // Top right
	glTexCoord2f(0, 0);
    glVertex3f(x, y, 0);
	glTexCoord2f(1, 0);
    glVertex3f(x + textRect.w, y, 0);
	glTexCoord2f(1, 1);
    glVertex3f(x + textRect.w, y + textRect.h, 0);

    // Bottom left
    glTexCoord2f(0, 0);
    glVertex3f(x, y, 0);
    glTexCoord2f(0, 1);
    glVertex3f(x, y + textRect.h, 0);
    glTexCoord2f(1, 1);
    glVertex3f(x + textRect.w, y + textRect.h, 0);

    glEnd();
    glPopMatrix();

    SDL_GL_UnbindTexture(this->imageTexture);
}

Unknown::Graphics::Image::Image(const std::string &filename) : Image(filename.c_str()) {}
