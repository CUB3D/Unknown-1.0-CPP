//
// Created by cub3d on 10/07/2018.
//

#include "BasicTileMapRenderer.h"
#include <utility>
#include "../Unknown.h"

Unknown::BasicTileMapRenderer::BasicTileMapRenderer(Map &map1, std::function<void(int, int, int, int)> renderer1,
                                                    bool isGlobal) : map(map1), renderer(std::move(renderer1)) {
    if(isGlobal) {
        registerHook([&] { this->render(); }, HookType::RENDER);
    }
    this->camera.setPosition(0, 0, map.mapSize.width, map.mapSize.height);
}

void Unknown::BasicTileMapRenderer::render() const {
    auto bounds = camera.getTileBounds();

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

//TODO: gethook interface, returns function that will call the render hook