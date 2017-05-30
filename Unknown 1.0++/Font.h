#ifndef FONT_H
#define FONT_H

#include <string>
#include "Image.h"
#include "Unknown.h"

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
			Font(Image* fontSheet, const std::string layout, const int charSize);

			void drawChar(const char c, const int x, const int y);
			void drawString(const std::string string, const int x, const int y);
		};
	}
}
#endif