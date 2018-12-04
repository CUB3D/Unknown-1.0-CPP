//
// Created by cub3d on 01/08/18.
//

#include "TimerComponent.h"
#include <rttr/registration>

Unknown::TimerComponent::TimerComponent(const long long int time) : t(time) {}

//TODO: figure out this
RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<TimerComponent>("TimerComponent");
        //.constructor<>();
};
