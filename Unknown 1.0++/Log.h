#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#define UK_LOG_LEVEL_INFO 0
#define UK_LOG_LEVEL_WARNING 1
#define UK_LOG_LEVEL_ERROR 2

namespace Unknown {
	extern std::string logStatus[];

    void log(int logLevel, std::initializer_list<std::string> args);
}


#define UK_LOG_INFO(msg, ...) ::Unknown::log(UK_LOG_LEVEL_INFO, {msg, ##__VA_ARGS__})
#define UK_LOG_WARN(msg, ...) ::Unknown::log(UK_LOG_LEVEL_WARNING, {msg, ##__VA_ARGS__})
#define UK_LOG_ERROR(msg, ...) ::Unknown::log(UK_LOG_LEVEL_ERROR, {msg, ##__VA_ARGS__})
// __FUNCTION__
#define UK_LOG_INFO_VERBOSE(msg, ...) ::Unknown::log(UK_LOG_LEVEL_INFO, {msg, ##__VA_ARGS__, "@ [", __FILE__, ":",  ::Unknown::intToString(__LINE__), "]"})
#define UK_LOG_ERROR_VERBOSE(msg, ...) ::Unknown::log(UK_LOG_LEVEL_ERROR, {msg, ##__VA_ARGS__, "@ [", __FILE__, ":", ::Unknown::intToString(__LINE__), "]"})
#define UK_LOG_WARN_VERBOSE(msg, ...) ::Unknown::log(UK_LOG_LEVEL_WARN, {msg, ##__VA_ARGS__, "@ [", __FILE__, ":", ::Unknown::intToString(__LINE__), "]"})
