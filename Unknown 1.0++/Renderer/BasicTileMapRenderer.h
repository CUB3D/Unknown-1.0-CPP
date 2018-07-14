//
// Created by cub3d on 10/07/2018.
//

#ifndef UK_BASICTILEMAPRENDERER_H
#define UK_BASICTILEMAPRENDERER_H

#include <functional>

#include "Map.h"

namespace Unknown {

class BasicTileMapRenderer
{
protected:
    Map& map;
    std::function<void(int, int, int, int)> renderer;

public:
    BasicTileMapRenderer(Map& map1, std::function<void(int, int, int, int)> renderer1);
    virtual void render() const;
};

}


#endif
