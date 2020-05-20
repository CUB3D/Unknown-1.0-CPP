//
// Created by cub3d on 14/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_STATICTEXT_H
#define UNKNOWN_DEVELOPMENT_TOOL_STATICTEXT_H

#include "TTFont.h"
#include "FontGlyph.h"
#include "Graphics/RenderingBackend.h"

namespace Unknown {
    class StaticText {
    public:
        TextureInfo texture;
        VertexInfo verts;
        Dimension<int> size;

        StaticText(TTFont &font, const std::string &text, const Colour &col);

        void render(const int x, const int y) const;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_STATICTEXT_H
