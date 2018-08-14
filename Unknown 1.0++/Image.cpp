#include "stdafx.h"
#include "Image.h"

#include <SDL_image.h>
#include <iostream>
#include <string.h>

#include "Unknown.h"
#include "GL/glad/glad.h"


void Unknown::Graphics::Image::init()
{
	auto& uk = getUnknown();

	SDL_Surface* imageSurface = IMG_Load(this->filename.c_str());

	if (!imageSurface) {
		printf("Error: failed to load image, %s\n", IMG_GetError());
		uk.quit(ErrorCodes::SDL_IMAGE_LOAD_FAIL);
	}

	this->imageSize.width = imageSurface->w;
	this->imageSize.height = imageSurface->h;

	glGenTextures(1, &this->textureID);
	glBindTexture(GL_TEXTURE_2D, this->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//how the texture should wrap in t direction
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//how the texture lookup should be interpolated when the face is smaller than the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//how the texture lookup should be interpolated when the face is bigger than the texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int nOfColors = imageSurface->format->BytesPerPixel;
    int mode = GL_RGBA;
    if( nOfColors == 4 )     // contains an alpha channel
    {
        if(imageSurface->format->Rmask == 0x000000ff) {
            mode = GL_RGBA;
        } else {
            mode = GL_BGRA;
        }
    } else if( nOfColors == 3 ) {
        if(imageSurface->format->Rmask == 0x000000ff) {
            mode = GL_RGB;
        } else {
            mode = GL_BGR;
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSurface->w, imageSurface->h, 0, mode, GL_UNSIGNED_BYTE, imageSurface->pixels);

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
    auto& uk = getUnknown();

	SDL_Rect textRect;
	textRect.x = x;
	textRect.y = y;
	textRect.w = this->imageSize.width;
	textRect.h = this->imageSize.height;

    int centerX = (x + textRect.w / 2);
    int centerY = (y + textRect.h /2);

    glPushMatrix();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_MODELVIEW);
    glTranslated(centerX, centerY, 0);
    glRotated(angle, 0, 0, 1);
    glTranslated(-centerX, -centerY, 0);

    glColor4f(1, 1, 1, 1);

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

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);


    glEnd();
    glPopMatrix();
}

Unknown::Graphics::Image::Image(const std::string &filename) : filename(filename), textureID(0) {
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

Unknown::Graphics::Image::~Image() {}
