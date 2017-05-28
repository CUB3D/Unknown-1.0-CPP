#ifndef UI_H
#define UI_H

#include <string>

#include "Colour.h"
#include "Utils.h"
#include "Font.h"

#include <vector>
#include <memory>

namespace Unknown
{
	class Colour;

    enum UIComponent_Type
    {
		UI_NULL,
        UI_RECT,
        UI_SQUARE,
		UI_TEXT
    };

    class UIComponent
    {
        public:
            Graphics::Font* font;
            std::string name;
            UIComponent_Type type;
            Dimension<int> size;
            Point<int> location;
            Colour* colour;
            std::string parentName;
            std::string content; // consider moving to a subclass
            
			UIComponent();
            UIComponent(const UIComponent_Type type);            

            virtual void render() const;
    };

    class RectComponent : public UIComponent
    {
        public:
            RectComponent();
            virtual void render() const override;
    };

	class SquareComponent : public UIComponent
	{
		public:
			SquareComponent();
			virtual void render() const override;

	};

    class TextComponent : public UIComponent
    {
    public:
        TextComponent();
        virtual void render() const override;

    };

	class UIContainer
	{
	public:
        UIContainer();
		std::vector<std::unique_ptr<UIComponent>> components;

		void renderUI();
	};
}

#endif
