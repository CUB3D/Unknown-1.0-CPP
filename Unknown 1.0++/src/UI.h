#ifndef UI_H
#define UI_H

#include <string>
#include <Types/Colour.h>
#include <Utils.h>
#include <Font/Font.h>
#include <Event/Event.h>
#include <Renderer/IRenderable.h>
#include <vector>
#include <memory>

namespace Unknown
{
	class Colour;
	class Font;

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
			std::shared_ptr<Font> font;
            std::string name;
            UIComponent_Type type;
            Dimension<int> size;
            Point<int> location;
            std::shared_ptr<Colour> colour;
            std::string parentName;
            std::string content; // consider moving to a subclass

			UIComponent();
			UIComponent(const UIComponent_Type type);
			UIComponent(std::shared_ptr<Font> font, const UIComponent_Type type, std::string name, Point<int> location, Dimension<int> size);

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
		void mouseListener(Event &evnt);
		virtual void render() const override;
		virtual void init() override;
	};

    class TextBoxComponent : public UIComponent
    {
    public:
        bool isEditing = false;
        bool isNumerical = false;

        TextBoxComponent();
        TextBoxComponent(std::string name, std::shared_ptr<Font> font, ::Unknown::Point<int> location, ::Unknown::Dimension<int> size);
        void onKeyTyped(Event& evnt);
        void onMouseClick(Event &evnt);
        virtual void render() const override;
        virtual void init() override;
    };

    class ImageComponent : public UIComponent
	{
	public:
		std::shared_ptr<Image> image;

		ImageComponent();
		virtual void render() const override;
		virtual void init() override;
	};

    struct UIEvent
    {
        std::string componentName;
        std::string action;
        std::string relatedKey;
    };

    void registerUIListener(std::function<void(std::shared_ptr<UIEvent>)> listener, std::string listenerID);
    void removeUIListener(std::string listnerID);
    void callUIListeners(std::shared_ptr<UIEvent> evnt);

    #define UK_ADD_UI_LISTENER_INTERNAL(listener, id) ::Unknown::registerUIListener([this](std::shared_ptr<::Unknown::UIEvent> evnt) {listener(evnt);}, id)
    #define UK_ADD_UI_LISTENER_EXTERNAL(listener, id) ::Unknown::registerUIListener([](std::shared_ptr<::Unknown::UIEvent> evnt) {listener(evnt);}, id)
    #define UK_REMOVE_UI_LISTENER(id) ::Unknown::removeUIListener(id)

	class UIContainer : public IRenderable
	{
	public:
        UIContainer();
		std::vector<std::shared_ptr<UIComponent>> components;

		void setGlobalFont(std::shared_ptr<Font> font);
		std::shared_ptr<UIComponent> getComponentByName(const std::string name);
		std::string getComponentValue(const std::string& name);

		virtual void render(double Xoffset, double Yoffset) const override ;
		virtual Rect<int> getRenderBounds() override;
        void initUI();

        void addComponent(std::shared_ptr<UIComponent> component);
	};
}

#endif
