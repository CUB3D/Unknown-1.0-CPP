//
// Created by cub3d on 31/10/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_RENDERTEST2D_H
#define UNKNOWN_DEVELOPMENT_TOOL_RENDERTEST2D_H

#include <UK.h>


class RenderTest2D : public Unknown::Scene {
public:
    RenderTest2D();

    virtual void render() const override;
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_RENDERTEST2D_H
