#ifndef UTILS_H
#define UTILS_H

#define PI 3.141592653589793238462

#include "Types/Colour.h"
#include "document.h"
#include <vector>
#include <memory>
#include <random>
#include "Types/Point.h"


namespace Unknown {
	std::shared_ptr<Colour> getColourFromString(std::string str);

	bool isCharCodeNumber(const char* key);
	bool isStringNumerical(const std::string& str);

	std::vector<std::string> tokenise(std::string input, std::vector<std::string> extraTokens);

	long long randInt(const int min, const int max);

    bool stringToInt(const std::string& str, int& out);
}

#define RANDINT(min, max) ::Unknown::randInt(min, max)

#endif
