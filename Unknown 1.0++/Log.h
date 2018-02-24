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

    //TODO: move to utils
    template<class T1, class... Types>
    std::string concat(T1 first, Types... asf)
    {
        std::stringstream ss;
        //ss << first << " ";
        ((ss << asf), ...);

        return ss.str();
    }

	void log(int logLevel, std::string message);
}


#define UK_LOG_INFO(msg) ::Unknown::log(UK_LOG_LEVEL_INFO, msg)
#define UK_LOG_WARN(msg) ::Unknown::log(UK_LOG_LEVEL_WARNING, msg)
#define UK_LOG_ERROR(msg) ::Unknown::log(UK_LOG_LEVEL_ERROR, msg)
#define UK_LOG_INFO_VERBOSE(msg) ::Unknown::log(UK_LOG_LEVEL_INFO, ::Unknown::concat(msg, " [", __FILE__, ":", __LINE__, "]"))
#define UK_LOG_ERROR_VERBOSE(msg) ::Unknown::log(UK_LOG_LEVEL_ERROR, ::Unknown::concat(msg, " [", __FILE__, "]"))
#define UK_LOG_WARN_VERBOSE(msg) ::Unknown::log(UK_LOG_LEVEL_WARN, ::Unknown::concat(msg, " [", __FILE__, "]"))
