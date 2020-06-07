//
// Created by cub3d on 19/05/2020.
//

#ifndef UNKNOWN_SDLWINDOWMANAGER_H
#define UNKNOWN_SDLWINDOWMANAGER_H

#include <glm/glm.hpp>

class SDLWindowManager {
public:
    glm::vec2 screenSize;
    SDL_Window* window;
    SDL_Renderer* windowRenderer;


    void init(int width, int height);
};


#endif //UNKNOWN_SDLWINDOWMANAGER_H
