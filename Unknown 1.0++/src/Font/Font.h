#ifndef FONT_H
#define FONT_H

#include <string>
#include <Image.h>
#include <Unknown.h>
#include <SDL_ttf.h>

namespace Unknown {
	class Font {
	public:
		const int fontSize;

		explicit Font(const int fontSize);

		virtual void init() = 0;

		virtual void drawString(const std::string& string, const int x, const int y) const;
		virtual void drawChar(const char c, const int x, const int y) const = 0;

		virtual int getStringWidth(const std::string &str) const = 0;
		virtual int getCharWidth(const char c) const = 0;
		virtual int getStringHeight(const std::string &str) const;
	};
}
#endif