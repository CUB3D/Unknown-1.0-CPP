#include "stdafx.h"
#include "Log.h"
#include <iostream>

namespace Unknown
{
	char* Unknown::logStatus[] = { "[INFO] ", "[WARNING] ", "[ERROR] " };

	void log(int logLevel, const char* message)
	{
		printf(logStatus[logLevel]);

		printf(message);

		printf("\n");
	}
}
