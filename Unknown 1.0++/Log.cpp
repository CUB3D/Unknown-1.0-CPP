#include <cstdarg>
#include "stdafx.h"
#include "Log.h"
#include <initializer_list>

namespace Unknown
{
	std::string logStatus[] = { "INFO", "WARN", "ERR" };

    void log(int logLevel, std::initializer_list<std::string> args) {
        std::stringstream ss;

        auto arg = args.begin();

        while(true) {
            ss << *arg;
            arg++;
            if(arg == args.end()) {
                break;
            }
            ss << " ";
        }
        printf("[%s]: %s\n", logStatus[logLevel].c_str(), ss.str().c_str());
    }
}
