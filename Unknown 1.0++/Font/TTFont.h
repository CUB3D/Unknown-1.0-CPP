//
// Created by cub3d on 14/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_TTFFONT_H
#define UNKNOWN_DEVELOPMENT_TOOL_TTFFONT_H

#include "Font.h"
#include "../Colour.h"
#include "FontGlyph.h"
#include "../IInitable.h"

namespace Unknown
{
    namespace Graphics
    {
        class TTFont : public Font, public IInitable
        {
        private:
            TTF_Font* font;
            ::Unknown::Colour colour;
            std::map<char, FontGlyph> glyphMap;

        public:
            TTFont(const std::string& name, const int size, const Colour& colour);

            virtual void drawString(const std::string& string, const int x, const int y) const;
            virtual void drawChar(const char c, const int x, const int y) const;

            virtual int getStringWidth(const std::string &str) const override;
            virtual int getCharWidth(const char c) const override;
            virtual int getStringHeight(const std::string &str) const override;

            virtual void init() override;

            FontGlyph getGlyph(const char c) const;
        };
    }
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_TTFFONT_H
