//
// Created by cub3d on 29/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_COMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_COMPONENT_H

#include <string>
#include <memory>

namespace Unknown {
    class Entity;
    class Scene;

    class Component {
    public:
        virtual void update(Entity &ent);
        virtual void render(const Entity &ent, double Xoffset, double Yoffset) const;

        virtual void onDisable(Entity& ent);
        virtual void onEnable(Scene& scene, std::shared_ptr<Entity> ent);

        virtual void populateEditor();
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_COMPONENT_H
