//
// Created by cub3d on 06/12/18.
//

#include "SceneElementPrototype.h"
#include <rttr/registration>

RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<SceneElementPrototype>("ScenePrototype")
        .property("Name", &SceneElementPrototype::name)
        .property("Position", &SceneElementPrototype::position)
        .constructor<>();
};
