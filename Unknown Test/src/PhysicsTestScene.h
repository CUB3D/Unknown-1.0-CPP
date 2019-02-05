//
// Created by cub3d on 28/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_PHYSICSTESTSCENE_H
#define UNKNOWN_DEVELOPMENT_TOOL_PHYSICSTESTSCENE_H

#include "Scene/Scene.h"
#include "Scene/Scene.h"

class PhysicsTestScene : public ::Unknown::Scene
{
public:
    PhysicsTestScene();

    virtual void update() override;
    virtual void render() const override;

};


#endif //UNKNOWN_DEVELOPMENT_TOOL_PHYSICSTESTSCENE_H
