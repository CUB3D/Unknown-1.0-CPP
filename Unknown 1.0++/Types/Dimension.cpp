//
// Created by cub3d on 15/11/18.
//

#include "Dimension.h"
#include <rttr/registration>

RTTR_REGISTRATION {
    using namespace Unknown;

    rttr::registration::class_<Dimension<int>>("Dimension<int>")
        .constructor<>()
        .property("Width", &Dimension<int>::width)
        .property("Height", &Dimension<int>::height);
};