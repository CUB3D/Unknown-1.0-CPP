//
// Created by cub3d on 23/11/18.
//

#include "EntityPrototype.h"
#include <rttr/registration>
#include <Entity/Component.h>

RTTR_REGISTRATION {
    using namespace Unknown;

    rttr::registration::class_<EntityPrototype>("EntityPrototype")
            .property("Tag", &EntityPrototype::tag)
            .property("Size", &EntityPrototype::size)
            // Removed as currently no support for parsing arrays
           // .property("Components", &EntityPrototype::components)
            .constructor<>();
};
