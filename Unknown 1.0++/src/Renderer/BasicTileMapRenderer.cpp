//
// Created by cub3d on 10/07/2018.
//

#include "BasicTileMapRenderer.h"
#include <utility>
#include <Unknown.h>

Unknown::BasicTileMapRenderer::BasicTileMapRenderer(Map &map1, std::function<void(int, int, int, int)> renderer1,
                                                    bool isGlobal) : map(map1), renderer(std::move(renderer1)), camera(map.mapSize.width, map.mapSize.height) {
    if(isGlobal) {
        registerHook([&] { this->render(0, 0); }, HookType::RENDER);
    }
}

void Unknown::BasicTileMapRenderer::render(double Xoffset, double Yoffset) const {
    auto bounds = camera.getBounds();

    for(int x = bounds.x; x < bounds.w + bounds.x; x++) {
        for(int y = bounds.y; y < bounds.h + bounds.y; y++) {
            if(renderer) {
                renderer(x, y, map.getTileID(x, y), map.getData(x, y));
            }
        }
    }
}

Unknown::BasicTileMapRenderer::BasicTileMapRenderer(Map &map1,
                                                    std::function<void(int, int, int, int)> renderer1) : BasicTileMapRenderer(map1, renderer1, true){

}

Unknown::Rect<int> Unknown::BasicTileMapRenderer::getRenderBounds() {
    auto b = camera.getBounds();
    return Rect<int>(b.x, b.y, b.h, b.w);

}

//TODO: gethook interface, returns function that will call the render hook