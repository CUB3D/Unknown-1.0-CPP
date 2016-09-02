#ifndef UI_H
#define UI_H

#include <string>

#include "Colour.h"
#include "Utils.h"

#include <vector>

namespace Unknown
{
	class Colour;

    enum UIComponent_Type
    {
        UI_RECT,
        UI_SQUARE
    };

    class UIComponent
    {
        public:
            std::string name;
            UIComponent_Type type;
            Dimension<int> size;
            Point<int> location;
            Colour* colour;
            std::string parentName;
            std::string content; // consider moving to a subclass
            
            UIComponent(const UIComponent_Type type);            

            virtual void render() const;
    };

    class RectComponent : public UIComponent
    {
        public:
            RectComponent();
            virtual void render() const override;
    };

	class SquareComponent : public RectComponent
	{
		public:
			SquareComponent();
			virtual void render() const override;

	};

	class UIContainer
	{
	public:
		std::vector<UIComponent*> components;

		void renderUI();
	};
}

#endif
