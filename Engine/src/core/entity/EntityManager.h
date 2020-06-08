//
// Created by cub3d on 08/06/2020.
//

#ifndef UNKNOWN_ENTITYMANAGER_H
#define UNKNOWN_ENTITYMANAGER_H

#include <entt/entt.hpp>
#include <glm/glm.hpp>

struct EntityTag {
    std::string tag;
};

class EntityManager {
    entt::registry entityRegistry;
}

#endif //UNKNOWN_ENTITYMANAGER_H
