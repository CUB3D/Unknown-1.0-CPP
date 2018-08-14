//
// Created by cub3d on 14/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_BITMAPFONT_H
#define UNKNOWN_DEVELOPMENT_TOOL_BITMAPFONT_H

#include "Font.h"
#include "../Image.h"

namespace Unknown
{
    namespace Graphics
    {
        class BitmapFont : public Font
        {
        private:
            const std::string layout;
            Image fontSheet;

        public:
            BitmapFont(Image img, const std::string& layout, const int fontSize);

            virtual void drawChar(const char c, const int x, const int y) const;
            virtual int getStringWidth(const std::string &str) const override;

            virtual void init();
        };
    }
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_BITMAPFONT_H
