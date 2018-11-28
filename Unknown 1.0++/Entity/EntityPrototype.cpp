//
// Created by cub3d on 23/11/18.
//

#include "EntityPrototype.h"
#include <rttr/registration>
#include <Entity/Component.h>

RTTR_REGISTRATION {
    using namespace Unknown;

    rttr::registration::class_<EntityPrototype>("EntityPrototype")
            .constructor<>()
            .property("Tag", &EntityPrototype::tag)
            .property("Size", &EntityPrototype::size)
            .property("Components", &EntityPrototype::components);
};
