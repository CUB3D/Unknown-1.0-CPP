//
// Created by cub3d on 23/11/18.
//

#ifndef UNKNOWN_ENTITYPROTOTYPE_H
#define UNKNOWN_ENTITYPROTOTYPE_H

#include "../Types/Dimension.h"
#include "Component.h"
#include <string>
#include <vector>
#include <memory>

namespace Unknown {
    class EntityPrototype {
    public:
        std::string tag;
        Dimension<int> size;

        std::vector<std::shared_ptr<Component>> components;

        EntityPrototype() = default;
    };
}


#endif //UNKNOWN_ENTITYPROTOTYPE_H
