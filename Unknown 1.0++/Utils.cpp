#include "stdafx.h"
#include "Utils.h"

#include "Colour.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>

Unknown::Direction up(0, 1);
Unknown::Direction down(0, -1);
Unknown::Direction left(1, 0);
Unknown::Direction right(-1, 0);


rapidjson::Document Unknown::readJSONFile(const char* filename)
{
	std::ifstream config(filename);

	std::ostringstream oss;
	oss << config.rdbuf();
	std::string doc = oss.str();

	rapidjson::Document d;

	d.Parse<0>(doc.c_str());

	return d;
}
// TODO: optional
rapidjson::Value* Unknown::getValue(const char* name, const rapidjson::Type type, rapidjson::Document& doc)
{
	if (doc.HasMember(name))
	{
		rapidjson::Value* val = &doc[name];

		if (val->GetType() == type)
		{
			return val;
		}
		else
		{
			return NULL;
		}
	}
	return NULL;
}

inline int parseHexString(std::stringstream& stream, std::string str) {
	stream << std::hex << str[0];
	stream << std::hex << str[1];
	int x = 0;
	stream >> x;
	stream.clear();
	return x;
}

std::shared_ptr<Unknown::Colour> Unknown::getColourFromString(std::string str)
{
	std::stringstream strstream;

	// A R G B
	int colourParts[4];

	colourParts[3] = 255;

	if (str.length() >= 8) {
		colourParts[3] = parseHexString(strstream, str);
		str = str.erase(0, 2);
	}

	for(int i = 0; i < 3; i++) {
	    colourParts[i] = parseHexString(strstream, str);
	    str = str.erase(0, 2);
	}

	return std::make_shared<Colour>(colourParts[0], colourParts[1], colourParts[2], colourParts[3]);
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
        return !std::isdigit(c);
    }) == str.end();
}

std::string Unknown::intToString(const int x) {
	std::stringstream ss;
	ss << x;
	return ss.str();
}

std::vector<std::string> Unknown::tokenise(std::string input, std::vector<std::string> extTokens)
{
	const char* temp = input.c_str();

    std::vector<std::string> tokens;

	std::string token;
    std::string lastTokenType = "str";

	for(char c = ' '; *temp != '\0', c = *temp; temp++)
	{
        if(isCharCodeNumber(&c))
        {
            if(lastTokenType == "num")
            {
                token += c;
            } else {
                if(!token.empty())
                {
                    tokens.push_back(token);
                }
                token = "";
                lastTokenType = "num";
                token += c;
            }
        }
        else {
            if(lastTokenType == "str")
            {
                token += c;
            } else {
                if(!token.empty())
                {
                    tokens.push_back(token);
                }
                token = "";
                lastTokenType = "str";
                token += c;
            }
        }

        for(auto extToken : extTokens)
        {
            if(extToken == token)
            {
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
