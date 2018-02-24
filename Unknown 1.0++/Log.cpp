#include "stdafx.h"
#include "Log.h"

namespace Unknown
{
	std::string logStatus[] = { "[INFO] ", "[WARNING] ", "[ERROR] " };

	void log(int logLevel, std::string message)
	{
		printf("%s%s\n", logStatus[logLevel].c_str(), message.c_str());
	}
}
