//
// Created by cub3d on 10/07/2018.
//

#include "BasicTileMapRenderer.h"
#include "Unknown.h"

Unknown::BasicTileMapRenderer::BasicTileMapRenderer(Map& map1,
                                                    std::function<void(int, int, int, int)> renderer1) : map(map1), renderer(renderer1) {
    registerHook([&] {this->render();}, HookType::RENDER);
}

void Unknown::BasicTileMapRenderer::render() const {
    for(int x = 0; x < map.mapSize.width; x++) {
        for(int y = 0; y < map.mapSize.height; y++) {
            if(renderer) {
                renderer(x, y, map.getTileID(x, y), map.getData(x, y));
            }
        }
    }
}
