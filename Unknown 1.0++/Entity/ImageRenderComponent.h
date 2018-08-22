//
// Created by cub3d on 02/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_IMAGERENDERCOMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_IMAGERENDERCOMPONENT_H

#include "Component.h"
#include "../Image.h"

namespace Unknown
{
    class ImageRenderComponent : public Component
    {
    public:
        Graphics::Image img;
        int renderScale = 1;

        ImageRenderComponent(const std::string& filename, const int renderScale);

        virtual void render(const Entity &ent, double Xoffset, double Yoffset) const;
        virtual void populateEditor();

        virtual Rect<int> getRenderBounds(const Entity& ent);
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_IMAGERENDERCOMPONENT_H
