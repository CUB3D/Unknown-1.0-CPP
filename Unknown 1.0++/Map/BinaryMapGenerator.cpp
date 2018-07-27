//
// Created by cub3d on 22/07/2018.
//

#include "BinaryMapGenerator.h"

Unknown::BinaryMapGenerator::BinaryMapGenerator() : BasicMapGenerator([&](const int x, const int y) {return this->generateTile(x, y);}) {

}

std::pair<int, int> Unknown::BinaryMapGenerator::generateTile(const int x, const int y) {
    return std::pair<int, int>(RANDINT(0, 2), 0);
}
