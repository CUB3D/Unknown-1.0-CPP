#include "stdafx.h"
#include "Image.h"

#include <SDL_image.h>
#include <iostream>
#include <string.h>

#include "Unknown.h"
#include "GL/GL.h"
#include "Graphics/RenderingBackend.h"


void Unknown::Graphics::Image::init()
{
//	auto& uk = getUnknown();
//
//	SDL_Surface* imageSurface = IMG_Load(this->filename.c_str());
//
//	if (!imageSurface) {
//		printf("Error: failed to load image, %s\n", IMG_GetError());
//		uk.quit(ErrorCodes::SDL_IMAGE_LOAD_FAIL);
//	}
//
//	this->imageSize.width = imageSurface->w;
//	this->imageSize.height = imageSurface->h;
//
//	glGenTextures(1, &this->textureID);
//	glBindTexture(GL_TEXTURE_2D, this->textureID);
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
////how the texture should wrap in t direction
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
////how the texture lookup should be interpolated when the face is smaller than the texture
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
////how the texture lookup should be interpolated when the face is bigger than the texture
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    int nOfColors = imageSurface->format->BytesPerPixel;
//    int mode = GL_RGBA;
//    if( nOfColors == 4 )     // contains an alpha channel
//    {
//        if(imageSurface->format->Rmask == 0x000000ff) {
//            mode = GL_RGBA;
//        } else {
//            mode = GL_BGRA;
//        }
//    } else if( nOfColors == 3 ) {
//        if(imageSurface->format->Rmask == 0x000000ff) {
//            mode = GL_RGB;
//        } else {
//            mode = GL_BGR;
//        }
//    }
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSurface->w, imageSurface->h, 0, mode, GL_UNSIGNED_BYTE, imageSurface->pixels);

    TextureInfo info = getRendererBackend()->loadTexture(this->filename);
    this->textureInfo = info;

    this->imageSize.width = info.width;
    this->imageSize.height = info.height;
   // this->textureID = info.pointer;

    auto tmp = getRendererBackend()->createRectVerticies(0, 0, info.width, info.height);
   // this->vao = tmp.vao;
    //this->vbo = tmp.vbo;
    this->vertexInfo = tmp;

    // Will be offset by x/y when rendering
    // Init vbo
    constexpr const int SIZE = 6 * (3 + 4 + 2 + 3);
//    GLfloat data[SIZE] {
//        // Format is vertex coord
//        // Then colour
//        // Then texcoord
//        // Then normal
//        0, 0, 0,
//        1, 1, 1, 1,
//        0, 0,
//        0, 0, 1,
//
//        (GLfloat)imageSurface->w, 0, 0,
//        1, 1, 1, 1,
//        1, 0,
//        (GLfloat)imageSurface->w, 0, 1,
//
//        (GLfloat)imageSurface->w, (GLfloat)imageSurface->h, 0,
//        1, 1, 1, 1,
//        1, 1,
//        (GLfloat)imageSurface->w, (GLfloat)imageSurface->h, 1,
//
//        0, 0, 0,
//        1, 1, 1, 1,
//        0, 0,
//        0, 0, 1,
//
//        0, (GLfloat)imageSurface->h, 0,
//        1, 1, 1, 1,
//        0, 1,
//        0, (GLfloat)imageSurface->h, 1,
//
//        (GLfloat)imageSurface->w, (GLfloat)imageSurface->h, 0,
//        1, 1, 1, 1,
//        1, 1,
//        (GLfloat)imageSurface->w, (GLfloat)imageSurface->h, 1
//    };

//    GLfloat data[SIZE] {
//        // Format is vertex coord
//        // Then colour
//        // Then texcoord
//        // Then normal
//        0, 0, 0,
//        1, 1, 1, 1,
//        0, 0,
//        0, 0, 1,
//
//        (GLfloat)info.width, 0, 0,
//        1, 1, 1, 1,
//        1, 0,
//        (GLfloat)info.width, 0, 1,
//
//        (GLfloat)info.width, (GLfloat)info.height, 0,
//        1, 1, 1, 1,
//        1, 1,
//        (GLfloat)info.width, (GLfloat)info.height, 1,
//
//        0, 0, 0,
//        1, 1, 1, 1,
//        0, 0,
//        0, 0, 1,
//
//        0, (GLfloat)info.height, 0,
//        1, 1, 1, 1,
//        0, 1,
//        0, (GLfloat)info.height, 1,
//
//        (GLfloat)info.width, (GLfloat)info.height, 0,
//        1, 1, 1, 1,
//        1, 1,
//        (GLfloat)info.width, (GLfloat)info.height, 1
//    };

//    glGenBuffers(1, &vbo);
//
//    // Bind VBO and put data in it
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, SIZE * sizeof(GLfloat), data, GL_STATIC_DRAW);
//
//    glGenVertexArrays(1, &vao);
//
//    // Bind the VAO and fill in the locations of each piece of vertex data
//    glBindVertexArray(vao);
//    constexpr const int stride = (3 + 4 + 2 + 3) * sizeof(GLfloat); // Size of each sub block
//
//    // Verticies
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, 0);
//    // Colours
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void *>(3 * sizeof(GLfloat)));
//    // Texture coords
//    glEnableVertexAttribArray(2);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void *>((3 + 4) * sizeof(GLfloat)));
//    // Normals
//    glEnableVertexAttribArray(3);
//    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void *>((3 + 4 + 2) * sizeof(GLfloat)));
//
//    glBindVertexArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //SDL_FreeSurface(imageSurface);
}

void Unknown::Graphics::Image::render(const int x, const int y, const double angle, SDL_Rect* clip) const {
    getRendererBackend()->renderTexture(x, y, angle, this->textureInfo, this->vertexInfo);
    //auto& uk = getUnknown();

  //  int centerX = imageSize.width / 2;
    //int centerY = imageSize.height / 2;

    // Texture setup
    //glBindTexture(GL_TEXTURE_2D, this->textureID);

    // Texture parameters
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
////    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
////    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
////    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
////    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
////    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );


//    glBindVertexArray(vao);
//
//    // Render data
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//
//    // Unbind stuff
//    glBindVertexArray(0);
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
