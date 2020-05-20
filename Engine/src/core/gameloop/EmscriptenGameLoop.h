//
// Created by cub3d on 17/05/2020.
//

#ifndef UNKNOWN_EMSCRIPTENGAMELOOP_H
#define UNKNOWN_EMSCRIPTENGAMELOOP_H

#ifdef __EMSCRIPTEN__

#include "GameLoop.h"

class EmscriptenGameLoop : public GameLoop {
public:
    virtual void init() override;
    virtual void loop() override;
};

#endif


#endif //UNKNOWN_EMSCRIPTENGAMELOOP_H
