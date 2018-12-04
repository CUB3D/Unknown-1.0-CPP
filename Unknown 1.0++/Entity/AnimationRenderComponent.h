//
// Created by cub3d on 12/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_ANIMATIONRENDERCOMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_ANIMATIONRENDERCOMPONENT_H

#include "../Animation.h"
#include "Component.h"
#include "Entity.h"

namespace Unknown {
    class AnimationRenderComponent : public Component {
    public:
        Animation animation;

        AnimationRenderComponent(Animation animation1);

        virtual void render(const Entity& ent, double xoff, double yoff) const override;
        virtual void update(Entity& ent) override;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_ANIMATIONRENDERCOMPONENT_H
