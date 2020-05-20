//
// Created by cub3d on 18/05/2020.
//

#ifndef UNKNOWN_EVENT_H
#define UNKNOWN_EVENT_H

#include <glm/glm.hpp>

struct UpdateEvent {};
struct RenderEvent {};
struct EngineInitEvent {};

struct ResizeEvent {
    int width;
    int height;
};

struct KeyPressEvent {
    int SDLCode;
    bool pressed;
};

struct MouseEvent {
    int SDLButtonCode;
    bool buttonState;
    glm::vec2 location;
};

#endif //UNKNOWN_EVENT_H
