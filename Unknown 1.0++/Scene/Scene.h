//
// Created by cub3d on 01/06/17.
//

#ifndef UNKNOWN_1_0_CPP_SCENE_H
#define UNKNOWN_1_0_CPP_SCENE_H


#include <string>
#include <functional>
#include "Box2D/Box2D.h"

#include "../UI.h"
#include "../Font.h"
#include "../Renderer/IRenderable.h"

namespace Unknown
{
    class Scene
    {
    public:
        std::vector<std::shared_ptr<IRenderable>> renderables;
        b2World world;
        const std::string name;
        Scene(const std::string name);

        virtual void render() const; //TODO: this should render all renderables and when creating something renderable it should add itself to the current scene, also finish partial map rendering to only render
                // TODO:                         The section that is currently visible
        virtual void update();
    };

    class MenuScene : public Scene
    {
        std::string uiFile;
        std::shared_ptr<Graphics::Font> font;

    public:
        UIContainer menu;

        MenuScene(const std::string name, std::string uiFile, std::shared_ptr<Graphics::Font> font);

        virtual void render() const override;
        virtual void update() override;

        void reloadMenu();
    };

    class CustomScene : public Scene
    {
        const std::function<void(void)> renderer;
        const std::function<void(void)> updater;

    public:
        CustomScene(const std::string name, std::function<void(void)> renderer, std::function<void(void)> updater);
        virtual void render() const override;
        virtual void update() override;
    };
}


#endif //UNKNOWN_1_0_CPP_SCENE_H
