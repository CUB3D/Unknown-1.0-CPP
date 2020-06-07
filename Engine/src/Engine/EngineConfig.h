//
// Created by cub3d on 03/11/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_ENGINECONFIG_H
#define UNKNOWN_DEVELOPMENT_TOOL_ENGINECONFIG_H

#include <string>
#include "rttr/registration"
#include <glm/glm.hpp>

namespace Unknown {
    struct EngineConfig {

        EngineConfig();

        glm::vec2 targetSize;

        std::string title;
        int targetUPS;

        // Render Settings
        int rendererMode;
        bool MSAA;
        int vsync;
        bool textureFallback;

        bool editing;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_ENGINECONFIG_H
