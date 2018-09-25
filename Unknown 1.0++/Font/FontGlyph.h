//
// Created by cub3d on 14/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_FONTGLYPH_H
#define UNKNOWN_DEVELOPMENT_TOOL_FONTGLYPH_H

#include <SDL_ttf.h>
#include "../Colour.h"
#include "../Utils.h"

#include "../GL/GL.h"
#include "../Graphics/RenderingBackend.h"

namespace Unknown
{
    namespace Graphics
    {
        class FontGlyph
        {
        public:
            TextureInfo texture;
            VertexInfo verts;

           // GLuint textureID;
            Dimension<int> size;

            FontGlyph(const char c, TTF_Font *font, const Colour &col);

            void drawGlyph(const int x, const int y) const;
        };
    }
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_FONTGLYPH_H
