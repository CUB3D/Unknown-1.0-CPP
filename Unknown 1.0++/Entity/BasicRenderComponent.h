//
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_BASICRENDERCOMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_BASICRENDERCOMPONENT_H

#include "Component.h"
#include "../Colour.h"
#include "Reflex.h"

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
        virtual void update(Entity &ent);

        virtual void populateEditor() override;
    };

    REFLECT {
        addClass(BasicRenderComponent)
        ->addProp(col)
        ->addProp(renderScale);
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_BASICRENDERCOMPONENT_H
