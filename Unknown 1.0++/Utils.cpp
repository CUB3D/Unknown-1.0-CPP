#include "Utils.h"

#include <Types/Colour.h>

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <locale>

int Unknown::parseHexString(std::stringstream& stream, const std::string& str) {
	stream << std::hex << str[0];
	stream << std::hex << str[1];
	int x = 0;
	stream >> x;
	stream.clear();
	return x;
}

bool Unknown::stringToInt(const std::string& str, int& out) {
	if(str.empty()) {
		return false;
	}

    std::stringstream ss;
    ss << str;
    ss >> out;
    return !ss.bad();
}

long long Unknown::randInt(const int min, const int max) {
	std::random_device rnd;
	std::mt19937_64 rng(rnd());
	std::uniform_int_distribution<long long> uni(min, max);
	return uni(rng);
}

bool Unknown::isCharCodeNumber(const char* key)
{
	return *key >= '0' && *key <= '9';
}

bool Unknown::isStringNumerical(const std::string& str) {
    return !str.empty() && std::find_if(str.begin(), str.end(), [](char c) {
        return !std::isdigit(c, std::locale());
    }) == str.end();
}

std::vector<std::string> Unknown::tokenise(std::string input, std::vector<std::string> extTokens)
{
	const char* temp = input.c_str();

    std::vector<std::string> tokens;

	std::string token;
    std::string lastTokenType = "str";

	for(char c = ' '; c = *temp, *temp != '\0'; temp++)
	{
        if(isCharCodeNumber(&c))
        {
            if(lastTokenType == "num") {
                token += c;
            } else {
                if(!token.empty()) {
                    tokens.push_back(token);
                }
                token = "";
                lastTokenType = "num";
                token += c;
            }
        }
        else {
            if(lastTokenType == "str") {
                token += c;
            } else {
                if(!token.empty()) {
                    tokens.push_back(token);
                }
                token = "";
                lastTokenType = "str";
                token += c;
            }
        }

        for(const auto &extToken : extTokens) {
            if(extToken == token) {
				tokens.push_back(token);
                token = "";
            }
        }
	}

    if(!token.empty())
    {
        tokens.push_back(token);
    }

	return tokens;
}
