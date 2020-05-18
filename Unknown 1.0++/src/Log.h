//
// Created by cub3d on 18/05/2020.
//

#ifndef UNKNOWN_LOG_H
#define UNKNOWN_LOG_H

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Unknown {
    void log_init();
};

#define UK_INFO SPDLOG_INFO
#define UK_WARN SPDLOG_WARN
#define UK_ERROR SPDLOG_ERROR

#endif
