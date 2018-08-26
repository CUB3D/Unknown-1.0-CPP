#include "stdafx.h"
#include "Image.h"

#include <SDL_image.h>
#include <iostream>
#include <string.h>

#include "Unknown.h"
#include "GL/GL.h"


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


    // TODO: add ibo support

    // Will be offset by x/y when rendering
    // Init vbo
    constexpr const int SIZE = 6 * (3 + 4 + 2);
    GLfloat data[SIZE] {
        // Format is vertex coord
        // Then colour
        // Then texcoord
        // TODO: then normal
        0, 0, 0,
        1, 1, 1, 1,
        0, 0,

        (GLfloat)imageSurface->w, 0, 0,
        1, 1, 1, 1,
        1, 0,

        (GLfloat)imageSurface->w, (GLfloat)imageSurface->h, 0,
        1, 1, 1, 1,
        1, 1,

        0, 0, 0,
        1, 1, 1, 1,
        0, 0,

        0, (GLfloat)imageSurface->h, 0,
        1, 1, 1, 1,
        0, 1,

        (GLfloat)imageSurface->w, (GLfloat)imageSurface->h, 0,
        1, 1, 1, 1,
        1, 1
    };

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat), data, GL_STATIC_DRAW);

    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    SDL_FreeSurface(imageSurface);
}

void Unknown::Graphics::Image::render(const int x, const int y) const {
	this->render(x, y, 0);
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle) const {
	this->render(x, y, angle, NULL);
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle, SDL_Rect* clip) const {
    auto& uk = getUnknown();

    int centerX = imageSize.width / 2;
    int centerY = imageSize.height / 2;

    glPushMatrix();

    // Texture setup
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    // Texture config
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

glMatrixMode(GL_MODELVIEW);
    // Rotation and translation
    glLoadIdentity();

    glTranslated(x + centerX, y + centerY, 0);
    glRotated(angle, 0, 0, 1);
    glTranslated(-centerX, -centerY, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    constexpr const int stride = (3 + 4 + 2) * sizeof(GLfloat); // Size of each sub block
    glVertexPointer(3, GL_FLOAT, stride, 0);
    glColorPointer(4, GL_FLOAT, stride, reinterpret_cast<const void *>(3 * sizeof(GLfloat)));
    glTexCoordPointer(2, GL_FLOAT, stride, reinterpret_cast<const void *>((3 + 4) * sizeof(GLfloat)));

    // Render data
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Unbind stuff
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

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
