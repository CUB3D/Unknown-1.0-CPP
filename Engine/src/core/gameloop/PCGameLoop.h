//
// Created by cub3d on 17/05/2020.
//

#ifndef UNKNOWN_PCGAMELOOP_H
#define UNKNOWN_PCGAMELOOP_H

#include "GameLoop.h"

class PCGameLoop: public GameLoop {
public:
    void loop() override;
    void init() override;
};

#endif //UNKNOWN_PCGAMELOOP_H