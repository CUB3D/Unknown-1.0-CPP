//
// Created by cub3d on 22/07/2018.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_BASICMAPGENERATOR_H
#define UNKNOWN_DEVELOPMENT_TOOL_BASICMAPGENERATOR_H


#include <functional>
#include "../Map.h"

namespace Unknown
{
    class BasicMapGenerator
    {
        std::function<std::pair<int, int>(const int, const int)> generatorBackend;

    public:
        BasicMapGenerator(std::function<std::pair<int, int>(const int, const int)> backend);

        void generate(Map &map);
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_BASICMAPGENERATOR_H
