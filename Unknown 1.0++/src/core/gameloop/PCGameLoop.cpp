//
// Created by cub3d on 17/05/2020.
//
#include "PCGameLoop.h"
#include "Unknown.h"

void PCGameLoop::loop() {
    ::Unknown::getUnknown().doSingleLoopIttr();
}

void PCGameLoop::init() {
    while(running) {
        loop();
    }
}
