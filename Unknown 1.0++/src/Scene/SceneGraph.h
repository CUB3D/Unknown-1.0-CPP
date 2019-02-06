//
// Created by cub3d on 09/12/18.
//

#ifndef PROJECT_SCENEGRAPH_H
#define PROJECT_SCENEGRAPH_H

#include <Scene/SceneElementPrototype.h>
#include <vector>

namespace Unknown {
    class SceneElementPrototype;

    class SceneGraph {
    public:
        std::vector<SceneElementPrototype> sceneElements;
    };
}

#endif //PROJECT_SCENEGRAPH_H
