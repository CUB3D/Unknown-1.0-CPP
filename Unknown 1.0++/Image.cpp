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


    //TODO: switch to single packed vbo to reduce binding times
    // TODO: add ibo support

    // Will be offset by x/y when rendering
    // Init vbo
    GLfloat verticies[18] = {
        0, 0, 0,
        (GLfloat)imageSurface->w, 0, 0,
        (GLfloat)imageSurface->w, (GLfloat)imageSurface->h, 0,

        0, 0, 0,
        0, (GLfloat)imageSurface->h, 0,
        (GLfloat)imageSurface->w, (GLfloat)imageSurface->h, 0
    };

    GLfloat colours[4 * 6] {
        1, 1, 1, 1,
        1, 0, 1, 1,
        0, 1, 1, 1,

        1, 0, 1, 1,
        0, 1, 1, 1,
        1, 0, 1, 1
    };

    GLfloat texture[2 * 6] {
        0, 0,
        1, 0,
        1, 1,

        0, 0,
        0, 1,
        1, 1
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(3, &vbo[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glEnableVertexAttribArray(0);
    glBufferData(GL_ARRAY_BUFFER, 3 * 6 * sizeof(GLfloat), verticies, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glEnableVertexAttribArray(1);
    glBufferData(GL_ARRAY_BUFFER, 4 * 6 * sizeof(GLfloat), colours, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glEnableVertexAttribArray(2);
    glBufferData(GL_ARRAY_BUFFER, 2 * 6 * sizeof(GLfloat), texture, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glBindVertexArray(0);
    //glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // Create shaders
    int vertShader = glCreateShader(GL_VERTEX_SHADER);
    int fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    const GLchar* vert = ""
                         "#version 420\n"
                         "\n"
                         "in vec3 vertex_position;\n"
                         "\n"
                         "void main() {\n"
                         "  gl_Position = vec4(vertex_position, 1.0);\n"
                         "}";
    // todo: is null strlen shader
    glShaderSource(vertShader, 1, &vert, nullptr);
    glCompileShader(vertShader);

    const GLchar* frag = "#version 420\n"
                         "\n"
                         "uniform vec4 inputColour;\n"
                         "out vec4 fragColour;\n"
                         "\n"
                         "void main() {\n"
                         "  fragColour = inputColour;\n"
                         "}";
    glShaderSource(fragShader, 1, &frag, nullptr);
    glCompileShader(fragShader);

    prog = glCreateProgram();
    glAttachShader(prog, vertShader);
    glAttachShader(prog, fragShader);

    glLinkProgram(prog);
    glValidateProgram(prog);

    char err[3000];
    glGetProgramInfoLog(prog, 3000, nullptr, err);

    printf("Error: %s\n", err);

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
    // Rotation and translation for vbo
    glLoadIdentity();

    glTranslated(x + centerX, y + centerY, 0);
    glRotated(angle, 0, 0, 1);
    glTranslated(-centerX, -centerY, 0);

    //glUseProgram(prog);
    //int loc = glGetUniformLocation(prog, "inputColour");
    //glUniform4f(loc, 1, 1, 1, 1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glColorPointer(4, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glTexCoordPointer(2, GL_FLOAT, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    //glDrawElements(GL_TRIANGLES, 6, GL_FLOAT, 0);

    //glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);


   // glEnd();
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
