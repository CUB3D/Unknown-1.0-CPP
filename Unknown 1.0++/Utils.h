#ifndef UTILS_H
#define UTILS_H

#define PI 3.14

#include "rapidjson\document.h"


namespace Unknown
{
	struct Dimension
	{
		double width;
		double height;
	};

	struct Point
	{
		double x;
		double y;
	};

	::rapidjson::Document readJSONFile(const char* filename);
}

#endif