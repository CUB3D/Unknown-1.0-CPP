#include "stdafx.h"
#include "UI.h"

#include "UI2D.h"

void Unknown::UIContainer::renderUIComponentRect(UIComponent comp)
{
	Graphics::drawRect(comp.bounds[0], comp.bounds[1], comp.bounds[2], comp.bounds[3], *comp.colour);
}

void Unknown::UIContainer::renderUIComponent(UIComponent comp)
{
	if (comp.type == "Rect")
	{
		renderUIComponentRect(comp);
	}
}

void Unknown::UIContainer::renderUI()
{
	for (auto comp : components)
	{
		renderUIComponent(comp);
	}
}