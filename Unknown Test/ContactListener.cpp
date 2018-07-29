//
// Created by cub3d on 28/07/2018.
//

#include "ContactListener.h"

//TODO: check side of collision

void ContactListener::BeginContact(b2Contact *c) {
    onground = true;
}

void ContactListener::EndContact(b2Contact *c) {
    onground = false;
}
