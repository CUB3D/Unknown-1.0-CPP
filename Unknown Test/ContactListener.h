//
// Created by cub3d on 28/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_CONTACTLISTENER_H
#define UNKNOWN_DEVELOPMENT_TOOL_CONTACTLISTENER_H

#include "Box2D/Box2D.h"

class ContactListener : public b2ContactListener
{
public:
    bool onground = false;

    virtual void BeginContact(b2Contact* c) override;
    virtual void EndContact(b2Contact* c) override;
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_CONTACTLISTENER_H
