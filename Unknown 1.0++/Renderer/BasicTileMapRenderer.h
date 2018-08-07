//
// Created by cub3d on 10/07/2018.
//

#ifndef UK_BASICTILEMAPRENDERER_H
#define UK_BASICTILEMAPRENDERER_H

#include <functional>

#include "../Map.h"
#include "Camera.h"
#include "IRenderable.h"

namespace Unknown {

class BasicTileMapRenderer : public IRenderable
{
protected:
    Map& map;
    std::function<void(int, int, int, int)> renderer;
    int tileSize = 1;

public:
    Camera camera;

    BasicTileMapRenderer(Map &map1, std::function<void(int, int, int, int)> renderer1, bool isGlobal);
    BasicTileMapRenderer(Map& map1, std::function<void(int, int, int, int)> renderer1);
    virtual void render(double Xoffset, double Yoffset) const override;
    virtual Rect<int> getRenderBounds() override;
};

}


#endif
