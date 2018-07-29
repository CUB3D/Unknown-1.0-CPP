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

        virtual Rect<int> getRenderBounds();

        //TODO: tmp
        Entity* clone();
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_ENTITY_H
