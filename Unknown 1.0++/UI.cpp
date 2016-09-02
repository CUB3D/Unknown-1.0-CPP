#include "stdafx.h"
#include "UI.h"

#include "UI2D.h"

void Unknown::UIContainer::renderUI()
{
	for (auto comp : components)
	{
	    comp->render();
	}
}

// UIComponent

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