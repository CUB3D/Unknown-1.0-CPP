//
// Created by cub3d on 03/11/18.
//

#include "EngineConfig.h"

RTTR_REGISTRATION {
    rttr::registration::class_<Unknown::EngineConfig>("EngineConfig")
        .property("TargetHeight", &Unknown::EngineConfig::targetHeight)
        .property("TargetWidth", &Unknown::EngineConfig::targetWidth)
        .property("Title", &Unknown::EngineConfig::title)
        .property("TargetUPS", &Unknown::EngineConfig::targetUPS)
        .property("MSAA", &Unknown::EngineConfig::MSAA)
        .property("VSync", &Unknown::EngineConfig::vsync)
        .property("RendererMode", &Unknown::EngineConfig::rendererMode)
        .property("TextureFallback", &Unknown::EngineConfig::textureFallback)
        .constructor<>();
};

Unknown::EngineConfig::EngineConfig() :
targetHeight(0), targetWidth(0), title(""), targetUPS(60), MSAA(true), vsync(false), rendererMode(0),
textureFallback(true) {}
