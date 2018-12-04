//
// Created by cub3d on 15/11/18.
//

#include "Point.h"
#include <rttr/registration>

RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<Point<int>>("Point<int>")
            .property("X", &Point<int>::x)
            .property("Y", &Point<int>::y)
            .constructor<>();

    rttr::registration::class_<Point<double>>("Point<double>")
        .property("X", &Point<double>::x)
        .property("Y", &Point<double>::y)
        .constructor<>();
};