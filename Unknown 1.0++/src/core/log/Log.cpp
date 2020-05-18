//
// Created by cub3d on 18/05/2020.
//

#include "Log.h"

void Unknown::log_init() {
    auto out = spdlog::stdout_color_mt("console");
    auto err = spdlog::stderr_color_mt("stderr");
    out->info("Logging started");
}