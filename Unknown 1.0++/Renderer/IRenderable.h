//
// Created by cub3d on 18/07/2018.
//

#ifndef UNKNOWN_GAME_IRENDERABLE_H
#define UNKNOWN_GAME_IRENDERABLE_H

#include "../Utils.h"

namespace Unknown
{
    class IRenderable
    {
    public:
        virtual Rect<int> getRenderBounds() = 0;
        virtual void render(double Xoffset, double Yoffset) const = 0;
    };
}

#endif //UNKNOWN_GAME_IRENDERABLE_H
