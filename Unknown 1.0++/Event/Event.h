//
// Created by cub3d on 11/06/17.
//

#ifndef UNKNOWN_1_0_CPP_EVENT_H
#define UNKNOWN_1_0_CPP_EVENT_H

#include "../Input.h"

namespace Unknown
{
    class Event
    {
    public:
        int SDLCode;
        KeyCode keyCode;
        InputState keyState;
    };

    class KeyEvent : public Event
    {
    };

}

#endif //UNKNOWN_1_0_CPP_EVENT_H
