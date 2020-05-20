//
// Created by cub3d on 09/12/18.
//

#include "SceneGraph.h"
#include <rttr/registration>

RTTR_REGISTRATION {
    using namespace Unknown;
    rttr::registration::class_<SceneGraph>("SceneGraph")
            .property("SceneElements", &SceneGraph::sceneElements)
            .constructor<>();
};
