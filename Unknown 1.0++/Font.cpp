#include "stdafx.h"
#include "Font.h"

#include <iostream>

Unknown::Graphics::Font::Font(Image* fontSheet, const std::string layout, const int charSize) : fontSheet(fontSheet), layout(layout), charSize(charSize)
{
}

void Unknown::Graphics::Font::drawChar(const char character, const int x, const int y)
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

void Unknown::Graphics::Font::drawString(const std::string string, const int x, const int y)
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

