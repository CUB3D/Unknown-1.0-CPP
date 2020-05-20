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

    rttr::registration::class_<Dimension<float>>("Dimension<float>")
        .constructor<>()
        .property("Width", &Dimension<float>::width)
        .property("Height", &Dimension<float>::height);

    rttr::registration::class_<Dimension<double>>("Dimension<double>")
        .constructor<>()
        .property("Width", &Dimension<double>::width)
        .property("Height", &Dimension<double>::height);
};