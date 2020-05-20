//
// Created by cub3d on 09/12/18.
//

#ifndef PROJECT_BASEPROTOTYPE_H
#define PROJECT_BASEPROTOTYPE_H

#include <memory>

namespace Unknown {
    class Component;

    class BasePrototype {
    public:
        virtual std::shared_ptr<Component> create();
    };
}

#endif //PROJECT_BASEPROTOTYPE_H
