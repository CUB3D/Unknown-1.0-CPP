#include "stdafx.h"
#include "UI.h"

#include "UI2D.h"

#include <memory>

Unknown::UIContainer::UIContainer()
{
    //NOOP
}

void Unknown::UIContainer::renderUI()
{
	for (auto& comp : components)
	{
	    comp->render();
	}
}

void Unknown::UIContainer::setGlobalFont(Graphics::Font* font)
{
	for (auto& comp : components)
	{
		comp->font = font;
	}
}

std::unique_ptr<Unknown::UIComponent>* Unknown::UIContainer::getComponentByName(const std::string name)
{
	for (auto& comp : components)
	{
		if (comp->name == name)
		{
			return &comp;
		}
	}

	return NULL;
}

// UIComponent

Unknown::UIComponent::UIComponent() : UIComponent(UI_NULL)
{
	//NOOP
}

Unknown::UIComponent::UIComponent(const UIComponent_Type type) : type(type)
{
    this->size = {0, 0};
    this->location = {0, 0};
}

void Unknown::UIComponent::render() const
{
    //NOOP
}

// RectComponent

Unknown::RectComponent::RectComponent() : UIComponent(UI_RECT)
{
    //NOOP
}

void Unknown::RectComponent::render() const
{
    Graphics::drawRect(this->location.x, this->location.y, this->size.width, this->size.height, *this->colour);
}

// SquareComponent

Unknown::SquareComponent::SquareComponent() : UIComponent(UI_SQUARE)
{
	//NOOP
}

void Unknown::SquareComponent::render() const
{
	Graphics::drawRect(this->location.x, this->location.y, this->size.width, this->size.height, *this->colour);
}

// TextComponent

Unknown::TextComponent::TextComponent() : UIComponent(UI_TEXT)
{
    //NOOP
}

void Unknown::TextComponent::render() const
{
    if(font)
    {
        font->drawString(this->content, this->location.x, this->location.y);
    }
}