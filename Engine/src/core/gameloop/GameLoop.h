//
// Created by cub3d on 17/05/2020.
//

#ifndef UNKNOWN_GAMELOOP_H
#define UNKNOWN_GAMELOOP_H

#include <memory>

class GameLoop {
protected:
    bool running = true;
public:
    virtual void loop() = 0;
    virtual void init() = 0;
};

GameLoop& getGameLoop();

extern GameLoop& mainGameLoop;

#endif //UNKNOWN_GAMELOOP_H
