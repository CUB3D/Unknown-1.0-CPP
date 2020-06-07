//
// Created by cub3d on 23/11/18.
//

#ifndef UNKNOWN_ENTITYPROTOTYPE_H
#define UNKNOWN_ENTITYPROTOTYPE_H

#include <string>
#include <vector>
#include <memory>
#include "BasePrototype.h"
#include <glm/glm.hpp>

namespace Unknown {
    class Component;
    class Entity;

    class EntityPrototype {
    public:
        std::string tag;
        glm::vec2 size;

        std::vector<std::shared_ptr<Component>> components;

        EntityPrototype() = default;
    };
}


#endif //UNKNOWN_ENTITYPROTOTYPE_H
