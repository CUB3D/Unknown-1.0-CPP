//
// Created by cub3d on 16/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_ENTITYEDITOR_H
#define UNKNOWN_DEVELOPMENT_TOOL_ENTITYEDITOR_H

#include "../Entity/Entity.h"
#include <memory>
#include <array>

namespace Unknown
{
    class EntityEditor
    {
    public:
        std::shared_ptr<Entity> ent;
        std::array<char, 128> tag;
        double x;
        double y;
        double angle;

        EntityEditor(std::shared_ptr<Entity>&& ent);
        EntityEditor(std::shared_ptr<Entity>& ent);

        void init();

        void populateGui();
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_ENTITYEDITOR_H
