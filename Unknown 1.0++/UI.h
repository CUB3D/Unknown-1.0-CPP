#ifndef UI_H
#define UI_H

#include <string>

#include "Colour.h"
#include "Utils.h"
#include "Font.h"
#include "Event/Event.h"

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
		UI_TEXT,
		UI_BUTTON,
        UI_TEXTBOX
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
            virtual void init();
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

	class ButtonComponent : public UIComponent
	{
	public:
		ButtonComponent();
		void mouseListener(MouseEvent evnt);
		virtual void render() const override;
	};

    class TextBoxComponent : public UIComponent
    {
    public:
        bool isEditing = false;

        TextBoxComponent();
        void onKeyTyped(Event& evnt);
        void onMouseClick(MouseEvent evnt);
        virtual void render() const override;
        virtual void init() override;
    };

    struct UIEvent
    {
        std::string componentName;
        std::string action;
        const char** relatedKey;
    };

    extern std::map<std::string, std::function<void(const UIEvent)>> UIListeners;

    void registerUIListener(std::function<void(const UIEvent)> listener, std::string listenerID);
    void removeUIListener(std::string listnerID);
    void callUIListeners(const UIEvent evnt);

    #define UK_ADD_UI_LISTENER_INTERNAL(listener, id) ::Unknown::registerUIListener([this](::Unknown::UIEvent evnt) {listener(evnt);}, id)
    #define UK_ADD_UI_LISTENER_EXTERNAL(listener, id) ::Unknown::registerUIListener([](::Unknown::UIEvent evnt) {listener(evnt);}, id)
    #define UK_REMOVE_UI_LISTENER(id) ::Unknown::removeUIListener(id)

	class UIContainer
	{
	public:
        UIContainer();
		std::vector<std::unique_ptr<UIComponent>> components;

		void setGlobalFont(Graphics::Font* font);
		std::unique_ptr<UIComponent>* getComponentByName(const std::string name);

		void renderUI() const;
        void initUI();
	};
}

#endif
