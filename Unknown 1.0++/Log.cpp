#include "stdafx.h"
#include "Log.h"

namespace Unknown
{
	std::string logStatus[] = { "[INFO] ", "[WARNING] ", "[ERROR] " };

	void log(int logLevel, std::string message)
	{
		printf(logStatus[logLevel].c_str());

		printf(message.c_str());

		printf("\n");
	}
}
