#ifndef UTILS_H
#define UTILS_H

#define PI 3.14

#include "Colour.h"
#include "document.h"
#include <vector>
#include <memory>


namespace Unknown
{
	template < class T >
	class Dimension
	{
	public:
		T width;
		T height;

		Dimension() : Dimension(0, 0) {

		}

		Dimension(T t1, T t2) {
			this->width = t1;
			this->width = t2;
		}
	};

	template < class T >
	class Point
	{
	public:
		T x;
		T y;

		Point() : Point(0, 0) {

		}

		Point(T t1, T t2) {
			this->x = t1;
			this->y = t2;
		}
	};

	::rapidjson::Document readJSONFile(const char* filename);

	::rapidjson::Value* getValue(const char* name, const rapidjson::Type type, rapidjson::Document& doc);

	std::shared_ptr<Colour> getColourFromString(std::string str);

	bool isCharCodeNumber(const char* key);

	std::vector<std::string> tokenise(std::string input, std::vector<std::string> extraTokens);
}

#endif