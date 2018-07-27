//
// Created by cub3d on 22/07/2018.
//

#include "BasicMapGenerator.h"

void Unknown::BasicMapGenerator::generate(Unknown::Map &map) {
    for(int x = 0; x < map.mapSize.width; x++) {
        for(int y = 0; y < map.mapSize.height; y++) {
            auto tileData = this->generatorBackend(x, y);
            map(x, y) = tileData.first;
            map.setData(tileData.second, x, y);
        }
    }
}

Unknown::BasicMapGenerator::BasicMapGenerator(std::function<std::pair<int, int>(const int, const int)> backend) : generatorBackend(backend) {}
