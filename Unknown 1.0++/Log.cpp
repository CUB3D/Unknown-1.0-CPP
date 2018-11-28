#include <cstdarg>
#include <Log.h>
#include <initializer_list>
#include <sstream>
#include <string_view>

namespace Unknown
{
	std::string logStatus[] = { "INFO", "WARN", "ERR" };

    void log(int logLevel, std::initializer_list<std::string_view> args) {
        std::stringstream ss;

        const std::string_view* arg = args.begin();

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
