//
// Created by cub3d on 03/11/18.
//

#ifndef UNKNOWN_DEVELOPMENT_TOOL_ENGINECONFIG_H
#define UNKNOWN_DEVELOPMENT_TOOL_ENGINECONFIG_H

#include <string>
#include <rttr/registration.h>

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

RTTR_REGISTRATION {
    rttr::registration::class_<Unknown::EngineConfig>("EngineConfig")
            .property("TargetHeight", &Unknown::EngineConfig::targetHeight)
            .property("TargetWidth", &Unknown::EngineConfig::targetWidth)
            .property("Title", &Unknown::EngineConfig::title)
            .property("TargetUPS", &Unknown::EngineConfig::targetUPS)
            .property("MSAA", &Unknown::EngineConfig::MSAA)
            .property("VSync", &Unknown::EngineConfig::vsync)
            .property("RendererMode", &Unknown::EngineConfig::rendererMode);
};


#endif //UNKNOWN_DEVELOPMENT_TOOL_ENGINECONFIG_H
