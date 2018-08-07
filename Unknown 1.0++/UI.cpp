#include "stdafx.h"
#include "UI.h"

#include "UI2D.h"
#include "Event/Event.h"
#include "Event/EventManager.h"

#include <memory>
#include <ctime>
#include <regex>

std::map <std::string, std::function<void(std::shared_ptr<Unknown::UIEvent>)> > Unknown::UIListeners;

void Unknown::registerUIListener(std::function<void(std::shared_ptr<UIEvent>)> listener, std::string listenerID)
{
    UIListeners[listenerID] = listener;
}

void Unknown::removeUIListener(std::string listenerID)
{
    UIListeners.erase(listenerID);
}

void Unknown::callUIListeners(std::shared_ptr<UIEvent> evnt)
{
    std::map <std::string, std::function<void(std::shared_ptr<UIEvent>)> >::iterator listeners;

    for (listeners = UIListeners.begin(); listeners != UIListeners.end(); listeners++)
    {
		listeners->second(evnt);
    }
}

Unknown::UIContainer::UIContainer()
{
    //NOOP
}

void Unknown::UIContainer::render(double Xoffset, double Yoffset) const
{
    // Rendering
    for (auto& comp : components)
    {
        comp->render();
    }
}

void Unknown::UIContainer::setGlobalFont(std::shared_ptr<Graphics::Font> font)
{
	for (auto& comp : components)
	{
		comp->font = font;
	}
}

std::shared_ptr<Unknown::UIComponent> Unknown::UIContainer::getComponentByName(const std::string name)
{
	for (auto& comp : components)
	{
		if (comp->name == name)
		{
			return comp;
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

void Unknown::UIContainer::addComponent(std::shared_ptr<UIComponent> component)
{
    this->components.push_back(component);
}

std::string Unknown::UIContainer::getComponentValue(const std::string& name) {
    return getComponentByName(name)->content;
}

Unknown::Rect<int> Unknown::UIContainer::getRenderBounds() {
    //TODO: calculate total size
    return Rect<int>(1, 1, 1, 1);
}

// UIComponent

Unknown::UIComponent::UIComponent() : UIComponent(UI_NULL)
{
	//NOOP
}

Unknown::UIComponent::UIComponent(const UIComponent_Type type) : type(type), font(std::make_shared<Graphics::NullFont>())
{

}

void Unknown::UIComponent::render() const
{
    //NOOP
}

void Unknown::UIComponent::init()
{
    //NOOP
}

Unknown::UIComponent::UIComponent(std::shared_ptr<Graphics::Font> font, const UIComponent_Type type, std::string name, Point<int> location, Dimension<int> size) : font(font), name(name), location(location), size(size), type(type)
{

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

#include "SharedVariable.h"

void Unknown::TextComponent::render() const
{
	auto& variablelookup = ::Unknown::getUnknown()->variablelookup;

    std::string cpy(this->content);

    //TODO: this should somehow cache the shared var to remove need to re search

    std::regex var("\\$\\{.+\\}");
    std::smatch results;
    
	if(std::regex_search(this->content, results, var)) {

		for (int i = 0; i < results.size(); i++) {
			std::string resultStr = results[i];

			if (resultStr.empty())
				continue;
			std::string varname = resultStr.substr(2, resultStr.length() - 3);

			// TODO Does this work with multiple replacements, size of string might change
			for (auto &sharedVar : variablelookup) {
				if (sharedVar.first == varname) {
					std::string to = sharedVar.second->toString();
					cpy = cpy.replace(content.find(resultStr), resultStr.length(), to);
				}
			}
		}
	}

#ifdef NOPE
	for (auto result : results) {
		std::string resultStr = result.s;
		// std::string resultStr = std::string(result.first.base());
		if (resultStr.empty())
			continue;
		std::string varname = resultStr.substr(2, resultStr.length() - 3);

		// TODO Does this work with multiple replacements, size of string might change
		for (auto &sharedVar : variablelookup) {
			if (sharedVar.first == varname) {
				std::string to = sharedVar.second->toString();
				cpy = cpy.replace(content.find(resultStr), resultStr.length(), to);
			}
		}
	}
#endif // NOPE


    font->drawString(cpy, this->location.x, this->location.y);
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
                    std::shared_ptr<UIEvent> evnt = std::make_shared<UIEvent>();
                    evnt->componentName = this->name;
                    evnt->action = "buttonClicked";
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

	Colour col = *this->colour;

	if(mouseX >= this->location.x && mouseX <= this->location.x + this->size.width)
	{
		if (mouseY >= this->location.y && mouseY <= this->location.y + this->size.height)
		{
			col = Colour::WHITE;
		}
	}

	Graphics::drawRect(this->location.x, this->location.y, this->size.width, this->size.height, col);

	if(this->content.size() > 0)
	{
		font->drawString(this->content, this->location.x + (this->size.width / 2) - font->getStringWidth(this->content) / 2, this->location.y + this->size.height / 2 - font->getStringHeight(this->content) / 2);
	}
}

//TextBoxComponent
Unknown::TextBoxComponent::TextBoxComponent() : UIComponent(UI_TEXTBOX)
{
    //NOOP
}

void Unknown::TextBoxComponent::onKeyTyped(Event& evnt)
{
    if(this->isEditing)
    {
        if (evnt.keyState == InputState::PRESSED)
        {
            std::string key = std::string(SDL_GetKeyName(evnt.SDLCode));

            if(this->isNumerical) {
                if(!isStringNumerical(key)) {
                    printf("%s isn't numerical\n", key.c_str());
                    key="";
                }
            }

            std::shared_ptr<UIEvent> evnt_ = std::make_shared<UIEvent>();
            evnt_->componentName = this->name;
            evnt_->action = "keyTyped";
            evnt_->relatedKey = key;
            callUIListeners(evnt_);

            if (evnt.SDLCode == SDLK_BACKSPACE)
            {
                if (this->content.size() > 0)
                {
                    this->content.pop_back();
                }
            } else
            {
                this->content += evnt_->relatedKey;
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
    Graphics::drawRect(this->location.x, this->location.y, this->size.width, this->size.height, *this->colour);
    if(this->content.size() > 0)
    {
        font->drawString(this->content, this->location.x + 2, this->location.y);
    }

    if(isEditing)
    {

        if((time(NULL) % 1000) % 2 ==0)
        {
            Graphics::drawRect(this->location.x + font->getStringWidth(this->content) + 2, this->location.y + 2, 2, this->size.height - 4, Colour::BLACK);
        }
    }
}



void Unknown::TextBoxComponent::init()
{
    registerEventHandler(ET_KEYPRESS, this->name, [this](Event& evnt) {onKeyTyped(evnt);});
    UK_ADD_MOUSE_LISTENER_INTERNAL(this->onMouseClick, this->name);
}

Unknown::TextBoxComponent::TextBoxComponent(std::string name, std::shared_ptr<Graphics::Font> font, ::Unknown::Point<int> location, ::Unknown::Dimension<int> size) : UIComponent(font, UI_TEXTBOX, name, location, size)
{
}
