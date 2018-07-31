#include <cstdarg>
#include "stdafx.h"
#include "Log.h"
#include <initializer_list>

namespace Unknown
{
	std::string logStatus[] = { "INFO", "WARN", "ERR" };

	std::string concat(int n, const std::string &delim, ...) {
		va_list lst;
		va_start(lst, delim);

		std::stringstream ss;

		for(int i = 0; i < n; i++) {
			ss << va_arg(lst, std::string);

			if(i < n-1) {
				ss << delim;
			}
		}

		return ss.str();
	}

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
