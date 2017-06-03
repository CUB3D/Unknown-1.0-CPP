#include "stdafx.h"
#include "UI.h"

#include "UI2D.h"

#include <memory>

std::map <std::string, std::function<void(const Unknown::UIEvent)> > Unknown::UIListeners;

void Unknown::registerUIListener(std::function<void(const UIEvent)> listener, std::string listenerID)
{
    UIListeners[listenerID] = listener;
}

void Unknown::removeUIListener(std::string listenerID)
{
    UIListeners.erase(listenerID);
}

void Unknown::callUIListeners(const UIEvent evnt)
{
    std::map <std::string, std::function<void(const UIEvent)> >::iterator listeners;

    for (listeners = UIListeners.begin(); listeners != UIListeners.end(); listeners++)
    {
		listeners->second(evnt);
    }
}

Unknown::UIContainer::UIContainer()
{
    //NOOP
}

void Unknown::UIContainer::renderUI() const
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

void Unknown::UIContainer::initUI()
{
    for (auto& comp : components)
    {
        comp->init();
    }
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

void Unknown::UIComponent::init()
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

//ButtonComponent

Unknown::ButtonComponent::ButtonComponent() : UIComponent(UI_BUTTON)
{
	UK_ADD_MOUSE_LISTENER_INTERNAL(mouseListener, this->name);
}

void Unknown::ButtonComponent::mouseListener(MouseEvent evnt)
{
	if(evnt.mouseButton == MouseButton::BUTTON_LEFT)
	{
        if(evnt.buttonState == InputState::PRESSED)
        {
            if (evnt.location.x >= this->location.x && evnt.location.x <= this->location.x + this->size.width)
            {
                if (evnt.location.y >= this->location.y && evnt.location.y <= this->location.y + this->size.height)
                {
                    // If the button has been clicked
                    UIEvent evnt;
                    evnt.componentName = this->name;
                    evnt.action = "buttonClicked";
                    callUIListeners(evnt);
                }
            }
        }
	}
}


void Unknown::ButtonComponent::render() const
{
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);

	Colour* col = this->colour;

	if(mouseX >= this->location.x && mouseX <= this->location.x + this->size.width)
	{
		if (mouseY >= this->location.y && mouseY <= this->location.y + this->size.height)
		{
			col = &Colour::WHITE;
		}
	}

	Graphics::drawRect(this->location.x, this->location.y, this->size.width, this->size.height, *col);

	if(this->font && this->content.size() > 0)
	{
		font->drawString(this->content, this->location.x + (this->size.width / 2) - font->getStringWidth(this->content) / 2, this->location.y + this->size.height / 2 - font->getStringHeight(this->content) / 2);
	}
}

//TextBoxComponent
Unknown::TextBoxComponent::TextBoxComponent() : UIComponent(UI_TEXTBOX)
{
    //NOOP
}

void Unknown::TextBoxComponent::onKeyTyped(KeyEvent evnt)
{
    if(this->isEditing)
    {
        if (evnt.keyState == InputState::PRESSED)
        {
            const char *key = SDL_GetKeyName(evnt.SDLCode);

            UIEvent evnt_;
            evnt_.componentName = this->name;
            evnt_.action = "keyTyped";
            evnt_.relatedKey = &key;
            callUIListeners(evnt_);

            if (evnt.SDLCode == SDLK_BACKSPACE)
            {
                if (this->content.size() > 0)
                {
                    this->content.pop_back();
                }
            } else
            {
                this->content += key;
            }
        }
    }
}

void Unknown::TextBoxComponent::onMouseClick(MouseEvent evnt)
{
    if(evnt.buttonState == InputState::PRESSED)
    {
        if (evnt.location.x >= this->location.x && evnt.location.x <= this->location.x + this->size.width)
        {
            if (evnt.location.y >= this->location.y && evnt.location.y <= this->location.y + this->size.height)
            {
                // If the button has been clicked
                this->isEditing = true;
                return;
            }
        }

        this->isEditing = false;
    }
}

void Unknown::TextBoxComponent::render() const
{
    Graphics::drawRect(this->location.x, this->location.y, this->size.width, this->size.height, *(this->colour));
    if(this->font && this->content.size() > 0)
    {
        font->drawString(this->content, this->location.x + 2, this->location.y);
    }

    if(isEditing)
    {
        Graphics::drawRect(this->location.x + font->getStringWidth(this->content) + 2, this->location.y + 2, 2, this->size.height - 4, Colour::BLACK);
    }
}



void Unknown::TextBoxComponent::init()
{
    UK_ADD_KEY_LISTENER_INTERNAL(this->onKeyTyped, this->name);
    UK_ADD_MOUSE_LISTENER_INTERNAL(this->onMouseClick, this->name);
}