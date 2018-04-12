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

namespace Unknown
{
    class Scene
    {
    public:
        b2World world;
        const std::string name;
        Scene(const std::string name);

        virtual void render() const = 0;
        virtual void update();
    };

    class MenuScene : public Scene
    {
    public:
        UIContainer menu;

        MenuScene(const std::string name, std::string uiFile, std::shared_ptr<Graphics::Font> font);

        virtual void render() const override;
        virtual void update() override;
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
