#include "stdafx.h"
#include "Font.h"
#include "GL/glad/glad.h"

#include <iostream>
#include <SDL_ttf.h>

Unknown::Graphics::Font::Font(Image* fontSheet, const std::string layout, const int charSize) : fontSheet(fontSheet), layout(layout), charSize(charSize) {}

Unknown::Graphics::Font::Font() : Font(nullptr, "", 0)
{

}

void Unknown::Graphics::Font::drawChar(const char character, const int x, const int y) const
{
	fontSheet->textureRect.w = this->charSize;
	fontSheet->textureRect.h = this->charSize;

	int position = layout.find(character);

	SDL_Rect clip;
	clip.x = position * this->charSize;
	clip.y = 0;
	clip.w = this->charSize;
	clip.h = this->charSize;

	this->fontSheet->render(x, y, 0, &clip);
}

void Unknown::Graphics::Font::drawString(const std::string string, const int x, const int y) const
{
	for (int i = 0; i < string.size(); i++)
	{
		this->drawChar(string.c_str()[i], x + (i * this->charSize), y);
	}
}

int Unknown::Graphics::Font::getStringWidth(const std::string str) const
{
	return str.size() * this->charSize;
}

int Unknown::Graphics::Font::getStringHeight(const std::string str) const
{
    return this->charSize;
}

//TTFont

Unknown::Graphics::TTFont::TTFont(std::string name, const int size, Colour colour) : Font(NULL, "", 0)
{
    this->font = TTF_OpenFont(name.c_str(), size);

    if(!this->font) {
        printf("Error [Font]: %s\n", TTF_GetError());
    }

    this->color = colour.toSDLColour();
}

void Unknown::Graphics::TTFont::drawString(const std::string string, const int x, const int y) const
{
    //TODO: every character should have its own texture and they should be cached
    glPushMatrix();

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, string.c_str(), this->color);

	if(!textSurface) {
	    //TODO:
	}

	unsigned int texture;

    Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

    //TODO: why rerender
	SDL_Surface* tmp = SDL_CreateRGBSurface(0, textSurface->w, textSurface->h, 32, rmask, gmask, bmask, amask);
	SDL_BlitSurface(textSurface, NULL, tmp, NULL);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, 4, textSurface->w, textSurface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, tmp->pixels);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glEnable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);

    glMatrixMode(GL_MODELVIEW);

    glBegin(GL_TRIANGLES);
    // Top right
    glTexCoord2f(0, 0);
    glVertex3f(x, y, 0);
    glTexCoord2f(1, 0);
    glVertex3f(x + textSurface->w, y, 0);
    glTexCoord2f(1, 1);
    glVertex3f(x + textSurface->w, y + textSurface->h, 0);

    // Bottom left
    glTexCoord2f(0, 0);
    glVertex3f(x, y, 0);
    glTexCoord2f(0, 1);
    glVertex3f(x, y + textSurface->h, 0);
    glTexCoord2f(1, 1);
    glVertex3f(x + textSurface->w, y + textSurface->h, 0);

    glEnd();
    glPopMatrix();
}

int Unknown::Graphics::TTFont::getStringWidth(const std::string str) const
{
    int width = 0;
    TTF_SizeText(this->font, str.c_str(), &width, NULL);
    return width;
}

int Unknown::Graphics::TTFont::getStringHeight(const std::string str) const
{
    int height = 0;
    TTF_SizeText(this->font, str.c_str(), NULL, &height);
    return height;
}

Unknown::Graphics::NullFont::NullFont() : Font(nullptr, "", 0)
{

}

void Unknown::Graphics::NullFont::drawString(const std::string str, const int x, const int y) const
{
	//noop
}
