#include "stdafx.h"
#include "Utils.h"

#include "Colour.h"

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

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

Unknown::Colour* Unknown::getColourFromString(std::string str)
{
	int pos = 0;

	std::stringstream strstream;

	int alpha = 255;

	if (str.length() >= 8)
	{
		strstream << std::hex << str[pos++];
		strstream << std::hex << str[pos++];
		strstream >> alpha;

		strstream.clear();
	}

	strstream << std::hex << str[pos++];
	strstream << std::hex << str[pos++];
	int red = 0;
	strstream >> red;

	strstream.clear();

	strstream << std::hex << str[pos++];
	strstream << std::hex << str[pos++];
	int green = 0;
	strstream >> green;

	strstream.clear();

	strstream << std::hex << str[pos++];
	strstream << std::hex << str[pos];
	int blue = 0;
	strstream >> blue;

	return new Colour(red, green, blue, alpha);
}

bool Unknown::isCharCodeNumber(const char* key)
{
	return *key >= '0' && *key <= '9';
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