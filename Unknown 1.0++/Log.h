#pragma once

#define UK_LOG_LEVEL_INFO 0
#define UK_LOG_LEVEL_WARNING 1
#define UK_LOG_LEVEL_ERROR 2

namespace Unknown {
	extern char* logStatus[];

	void log(int logLevel, const char* message);
}

#define UK_LOG_INFO (msg) ::Unknown::log(UK_LOG_LEVEL_INFO, msg)
#define UK_LOG_WARN (msg) ::Unknown::log(UK_LOG_LEVEL_WARNING, msg)
#define UK_LOG_ERROR(msg) ::Unknown::log(UK_LOG_LEVEL_ERROR, msg)
