#ifndef UTILS_H
#define UTILS_H

#define PI 3.14

#include "Colour.h"
#include "document.h"
#include <vector>


namespace Unknown
{
	template < class T >
	struct Dimension
	{
		T width;
		T height;
	};

	template < class T >
	struct Point
	{
		T x;
		T y;
	};

	::rapidjson::Document readJSONFile(const char* filename);

	::rapidjson::Value* getValue(const char* name, const rapidjson::Type type, rapidjson::Document& doc);

	Colour* getColourFromString(std::string str);

	bool isCharCodeNumber(const char* key);

	std::vector<std::string> tokenise(std::string input, std::vector<std::string> extraTokens);
}

#endif