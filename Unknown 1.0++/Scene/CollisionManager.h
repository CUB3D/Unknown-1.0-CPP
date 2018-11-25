//
// Created by cub3d on 31/07/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_COLLISIONMANAGER_H
#define UNKNOWN_DEVELOPMENT_TOOL_COLLISIONMANAGER_H

#include <functional>
#include <map>
#include "Box2D/Box2D.h"
#include "../Entity/Entity.h"

namespace Unknown
{
    class Entity;

    class CollisionManager : public b2ContactListener
    {
        virtual void BeginContact(b2Contact *contact) override;

        virtual void EndContact(b2Contact *contact) override;

        std::map<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>, std::function<void(std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> objs, bool inContact)>> listeners;

    public:
        void addListener(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b,
                                                    std::function<void(std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>> objs, bool inContact)> callback);
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_COLLISIONMANAGER_H
