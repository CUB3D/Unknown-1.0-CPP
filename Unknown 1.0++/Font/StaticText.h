//
// Created by cub3d on 14/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_STATICTEXT_H
#define UNKNOWN_DEVELOPMENT_TOOL_STATICTEXT_H

#include "TTFont.h"
#include "FontGlyph.h"

class StaticText
{
public:
    GLuint textureID;
    Unknown::Dimension<int> size;

    StaticText(const Unknown::Graphics::TTFont &font, const std::string &text);
    void render(const int x, const int y) const;
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_STATICTEXT_H
