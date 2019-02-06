//
// Created by cub3d on 09/12/18.
//

#ifndef PROJECT_SCENEVIEWER_H
#define PROJECT_SCENEVIEWER_H

#include "ViewerBase.h"
#include <functional>

namespace Unknown {
    class SceneViewer : public ViewerBase<SceneViewer> {
    public:
        int selectedScene;

        virtual void render() override;
    };
}


#endif //PROJECT_SCENEVIEWER_H
