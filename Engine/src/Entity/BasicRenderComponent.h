//
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_BASICRENDERCOMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_BASICRENDERCOMPONENT_H

#include "Component.h"
#include <Types/Colour.h>
#include <Types/Rect.h>
#include <array>
#include <rttr/registration>

namespace Unknown
{
    class BasicRenderComponent : public Component
    {
    public:
        Colour col;
        int renderScale;

        std::array<float, 4> editorColour;

        BasicRenderComponent();
        BasicRenderComponent(Colour c);
        BasicRenderComponent(Colour c, int renderScale);

        virtual void render(const Entity &ent, double Xoffset, double Yoffset) const override;
        virtual void update(Entity &ent) override;

        virtual void populateEditor() override;

        virtual Rect<int> getRenderBounds(const Entity& ent);
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_BASICRENDERCOMPONENT_H
