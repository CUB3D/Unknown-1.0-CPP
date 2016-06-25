#pragma once

#include <string>
#include <vector>

#define UK_LOG_LEVEL_INFO 0
#define UK_LOG_LEVEL_WARNING 1
#define UK_LOG_LEVEL_ERROR 2

namespace Unknown {
	extern char* logStatus[];

	std::string concat(std::vector<std::string> strings);

	void log(int logLevel, const char* message);
}

#define UK_LOG_INFO(msg) ::Unknown::log(UK_LOG_LEVEL_INFO, msg)
#define UK_LOG_WARN(msg) ::Unknown::log(UK_LOG_LEVEL_WARNING, msg)
#define UK_LOG_ERROR(msg) ::Unknown::log(UK_LOG_LEVEL_ERROR, msg)
#define UK_LOG_INFO_VERBOSE(msg) ::Unknown::log(UK_LOG_LEVEL_INFO, ::Unknown::concat({msg, " [", __FILE__, "]"}).c_str())
#define UK_LOG_ERROR_VERBOSE(msg) ::Unknown::log(UK_LOG_LEVEL_ERROR, ::Unknown::concat({msg, " [", __FILE__, "]"}).c_str())
#define UK_LOG_WARN_VERBOSE(msg) ::Unknown::log(UK_LOG_LEVEL_WARN, ::Unknown::concat({msg, " [", __FILE__, "]"}).c_str())
