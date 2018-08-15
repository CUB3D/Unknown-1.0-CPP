//
// Created by cub3d on 11/06/17.
//

#ifndef UNKNOWN_1_0_CPP_EVENT_H
#define UNKNOWN_1_0_CPP_EVENT_H

#include "../Utils.h"

namespace Unknown
{
    enum InputState
    {
        RELEASED = 0,
        PRESSED = 1
    };

    enum EventType {
        ET_MOUSEBUTTON,
        ET_KEYPRESS,
        ET_WINDOW_RESIZE
    };

    struct KeyEvent {
        int SDLCode;
        InputState keyState;
    };

    struct ResizeEvent {
        int newWidth;
        int newHeight;
    };

    enum MouseButton
    {
        BUTTON_NONE,
        BUTTON_LEFT,
        BUTTON_RIGHT,
        BUTTON_MIDDLE
    };

    struct MouseEvent
    {
        int SDLButtonCode;
        MouseButton mouseButton;
        InputState buttonState;
        Point<int> location;
    };


    struct Event
    {
        KeyEvent key;
        ResizeEvent resize;
        MouseEvent mouse;

        EventType type;
    };

#define UK_ADD_MOUSE_LISTENER_INTERNAL(listener, id) ::Unknown::registerEventHandler(::Unknown::EventType::ET_MOUSEBUTTON, id, [this](::Unknown::Event& e){listener(e);})
#define UK_ADD_MOUSE_LISTENER_EXTERNAL(listener, id) ::Unknown::registerEventHandler(::Unknown::EventType::ET_MOUSEBUTTON, id, listener)
#define UK_REMOVE_MOUSE_LISTENER(id) ::Unknown::removeMouseListener(id)
}

#endif //UNKNOWN_1_0_CPP_EVENT_H
