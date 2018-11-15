//
// Created by cub3d on 03/11/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_ENGINECONFIG_H
#define UNKNOWN_DEVELOPMENT_TOOL_ENGINECONFIG_H

#include <string>
#include "rttr/registration"

namespace Unknown {
    struct EngineConfig {
        int targetHeight;
        int targetWidth;
        std::string title;
        int targetUPS;

        // Render Settings
        int rendererMode;
        bool MSAA;
        int vsync;
    };
}


#endif //UNKNOWN_DEVELOPMENT_TOOL_ENGINECONFIG_H
