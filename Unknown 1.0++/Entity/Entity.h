//
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_ENTITY_H
#define UNKNOWN_DEVELOPMENT_TOOL_ENTITY_H

#include "Component.h"
#include "../Renderer/IRenderable.h"
#include "../IUpdateable.h"
#include <vector>
#include "../Utils.h"

namespace Unknown
{
    class Component;

    class Entity : public IRenderable, public IUpdateable
    {
    public:
        std::vector<std::shared_ptr<Component>> components;

        Dimension<int> size;
        Point<double> position;


        Entity();

        virtual void update() override;
        virtual void render() const override;


        void setPosition(double x, double y);


        virtual Rect<int> getRenderBounds();

        template<typename T>
        std::shared_ptr<T> getComponent() {
            for(auto& component : this->components) {
                auto casted = std::dynamic_pointer_cast<T>(component);
                if(casted) {
                    return casted;
                }
            }

            return nullptr;
        }

        //TODO: tmp
        Entity* clone();
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_ENTITY_H
