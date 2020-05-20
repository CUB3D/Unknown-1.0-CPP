//
// Created by cub3d on 03/11/18.
//

#include "EngineConfig.h"

RTTR_REGISTRATION {
    using namespace Unknown;

    rttr::registration::class_<EngineConfig>("EngineConfig")
        .property("TargetSize", &EngineConfig::targetSize)
        .property("Title", &EngineConfig::title)
        .property("TargetUPS", &EngineConfig::targetUPS)
        .property("MSAA", &EngineConfig::MSAA)
        .property("VSync", &EngineConfig::vsync)
        .property("RendererMode", &EngineConfig::rendererMode)
        .property("TextureFallback", &EngineConfig::textureFallback)
        .property("Editing", &EngineConfig::editing)
        .constructor<>();
};

Unknown::EngineConfig::EngineConfig() :
targetSize(0, 0), title(""), targetUPS(60), MSAA(true), vsync(false), rendererMode(0),
textureFallback(true), editing(false) {}
