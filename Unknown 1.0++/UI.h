#ifndef UI_H
#define UI_H

#include <string>

#include "Colour.h"

#include <vector>

namespace Unknown
{
	class Colour;

	struct UIComponent
	{
		std::string name;
		std::string type;
		int bounds[4];
		Colour* colour;
		std::string insideComponent;
		int offsetBounds[4];
		std::string content;
	};

	class UIContainer
	{
	protected:
		void renderUIComponentRect(UIComponent comp);
		void renderUIComponent(UIComponent comp);

	public:
		std::vector<UIComponent> components;

		void renderUI();
	};
}

#endif
