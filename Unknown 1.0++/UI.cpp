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

Unknown::UIComponent::UIComponent()
{
    this->size = {0, 0};
    this->location = {0, 0};
}

void Unknown::UIComponent::render() const
{
    //NOOP
}

Unknown::RectComponent::RectComponent() : UIComponent()
{
    //NOOP
}

void Unknown::RectComponent::render() const
{
    Graphics::drawRect(this->location.x, this->location.y, this->size.width, this->size.height, *this->colour);
}
