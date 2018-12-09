//
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_COMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_COMPONENT_H

#include <string>

namespace Unknown {
    class Entity;

    class Component {
    public:
        virtual void update(Entity &ent);
        virtual void render(const Entity &ent, double Xoffset, double Yoffset) const;
        virtual void onDisable(Entity& ent);

        virtual void populateEditor();
        virtual const std::string getName();
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_COMPONENT_H
