//
// Created by cub3d on 01/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_TIMERCOMPONENT_H
#define UNKNOWN_DEVELOPMENT_TOOL_TIMERCOMPONENT_H

#include "Component.h"
#include <Timer.h>

namespace Unknown
{
    class TimerComponent : public Component
    {
    public:
        Timer t;

        TimerComponent(const long long int time);
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_TIMERCOMPONENT_H
