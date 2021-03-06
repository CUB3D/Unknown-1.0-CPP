#ifndef FONT_H
#define FONT_H

#include <string>
#include "Image.h"
#include "Unknown.h"

#include <SDL_ttf.h>

namespace Unknown
{
	namespace Graphics
	{
		class Font
		{
		private:
			const std::string layout;
			Image* fontSheet;
			const int charSize;

		public:
			Font();
			Font(Image* fontSheet, const std::string layout, const int charSize);

			void drawChar(const char c, const int x, const int y) const;

            virtual void drawString(const std::string string, const int x, const int y) const;

            virtual int getStringWidth(const std::string str) const;
            virtual int getStringHeight(const std::string str) const;
		};

        class TTFont : public Font
        {
        private:
            TTF_Font* font;
            SDL_Color color;

        public:
            TTFont(std::string name, const int size, Colour colour);

            virtual void drawString(const std::string string, const int x, const int y) const override;
            virtual int getStringWidth(const std::string str) const override;
            virtual int getStringHeight(const std::string str) const override;
        };

        class NullFont : public Font
        {
        public:
            NullFont();
            virtual void drawString(const std::string str, const int x, const int y) const override;

        };
	}
}
#endif