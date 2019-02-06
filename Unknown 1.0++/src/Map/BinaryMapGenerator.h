//
// Created by cub3d on 22/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_BINARYMAPGENERATOR_H
#define UNKNOWN_DEVELOPMENT_TOOL_BINARYMAPGENERATOR_H

#include "BasicMapGenerator.h"

namespace Unknown
{
    class BinaryMapGenerator : public BasicMapGenerator
    {
    public:
        BinaryMapGenerator();

        std::pair<int, int> generateTile(const int x, const int y);
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_BINARYMAPGENERATOR_H
