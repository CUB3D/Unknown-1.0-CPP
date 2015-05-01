#include "stdafx.h"
#include "Utils.h"

#include "rapidjson\document.h"

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

	printf("DOC: %s\n", doc.c_str());

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