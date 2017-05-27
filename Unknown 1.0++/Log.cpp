#include "stdafx.h"
#include "Log.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Unknown
{
	char* logStatus[] = { "[INFO] ", "[WARNING] ", "[ERROR] " };

	//TODO: move to utils
	std::string concat(std::vector<std::string> strings)
	{
		std::stringstream output;

		for (auto string : strings)
		{
			output << string;
		}

		return output.str();
	}

	void log(int logLevel, const char* message)
	{

		printf(logStatus[logLevel]);

		printf(message);

		printf("\n");
	}
}
