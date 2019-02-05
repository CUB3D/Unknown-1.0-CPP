//
// Created by cub3d on 14/08/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_RENDERTESTSCENE_H
#define UNKNOWN_DEVELOPMENT_TOOL_RENDERTESTSCENE_H

#include "Scene/Scene.h"

class RenderTestScene : public Unknown::Scene {
public:
    RenderTestScene();

    virtual void render() const;
    virtual void update();
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_RENDERTESTSCENE_H
