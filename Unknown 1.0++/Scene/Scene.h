//
// Created by cub3d on 01/06/17.
//

#ifndef UNKNOWN_1_0_CPP_SCENE_H
#define UNKNOWN_1_0_CPP_SCENE_H


#include <string>
#include <functional>
#include <Box2D/Box2D.h>

#include "../UI.h"
#include "../Font/Font.h"
#include "../Renderer/IRenderable.h"
#include "../IUpdateable.h"
#include "../ITagable.h"
#include "CollisionManager.h"
#include "../Renderer/Camera.h"

namespace Unknown
{
    class Scene
    {
    public:
        std::vector<std::shared_ptr<IRenderable>> renderables;
        std::vector<std::shared_ptr<IUpdateable>> updatables;
        std::vector<std::shared_ptr<ITagable>> tagables;
        std::vector<std::shared_ptr<Entity>> entities;
        b2World world;
        CollisionManager contactManager;
        Camera cam;


        const std::string name;
        Scene(const std::string name);

        virtual void render() const;
        virtual void update();

        template<class T>
        void addObject(std::shared_ptr<T> obj) {
            if(dynamic_cast<IRenderable*>(obj.get())) {
                renderables.push_back(std::dynamic_pointer_cast<IRenderable>(obj));
            }
            if(dynamic_cast<IUpdateable*>(obj.get())) {
                updatables.push_back(std::dynamic_pointer_cast<IUpdateable>(obj));
            }
            if(dynamic_cast<ITagable*>(obj.get())) {
                tagables.push_back(std::dynamic_pointer_cast<ITagable>(obj));
            }
            if(dynamic_cast<Entity*>(obj.get())) {
                entities.push_back(std::dynamic_pointer_cast<Entity>(obj));
            }
        }

        template<class T>
        std::shared_ptr<T> getObject(const std::string& str) {
            for (auto& tagable : this->tagables) {
                if(tagable->getTag() == str) {
                    if (dynamic_cast<T *>(tagable.get())) {
                        return std::dynamic_pointer_cast<T>(tagable);
                    }
                }
            }

            return nullptr;
        }

        template<typename T>
        std::vector<std::shared_ptr<T>> getObjects(const std::string& tag) const {
            std::vector<std::shared_ptr<T>> objs;
            for (auto& tagable : this->tagables) {
                if(tagable->getTag() == tag) {
                    if (dynamic_cast<T *>(tagable.get())) {
                        objs.push_back(std::dynamic_pointer_cast<T>(tagable));
                    }
                }
            }

            return objs;
        }
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

#define UK_LOAD_ENTITY_AT(name, x, y) ::Unknown::Loader::loadEntityAt(name, *this, x, y)


#endif //UNKNOWN_1_0_CPP_SCENE_H
