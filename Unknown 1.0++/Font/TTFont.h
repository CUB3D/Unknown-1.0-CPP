//
// Created by cub3d on 14/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_TTFFONT_H
#define UNKNOWN_DEVELOPMENT_TOOL_TTFFONT_H

#include "Font.h"
#include "Types/Colour.h"
#include "FontGlyph.h"
#include "../IInitable.h"

namespace Unknown
{
    namespace Graphics
    {
        class TTFont : public Font, public IInitable<>
        {
        private:
            ::Unknown::Colour colour;
            std::map<char, FontGlyph> glyphMap;

        public:
            TTF_Font* font;

            TTFont(const std::string& name, const int size, const Colour& colour);

            virtual void drawString(const std::string& string, const int x, const int y) const override;
            virtual void drawChar(const char c, const int x, const int y) const override;

            virtual int getStringWidth(const std::string &str) const override;
            virtual int getCharWidth(const char c) const override;
            virtual int getStringHeight(const std::string &str) const override;

            virtual void init() override;

            FontGlyph getGlyph(const char c) const;
        };
    }
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_TTFFONT_H
