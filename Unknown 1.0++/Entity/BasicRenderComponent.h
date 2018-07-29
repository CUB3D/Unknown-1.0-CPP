//
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_BASICRENDERCOMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_BASICRENDERCOMPONENT_H

#include "Component.h"
#include "../Colour.h"

namespace Unknown
{
    class BasicRenderComponent : public Component
    {
    public:
        Colour col;
        int renderScale;

        BasicRenderComponent(Colour c);
        BasicRenderComponent(Colour c, int renderScale);

        virtual void render(const Entity& ent) const override;
        virtual void update(Entity &ent);
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_BASICRENDERCOMPONENT_H
