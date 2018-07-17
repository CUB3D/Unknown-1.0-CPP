#ifndef UTILS_H
#define UTILS_H

#define PI 3.14

#include "Colour.h"
#include "document.h"
#include <vector>
#include <memory>
#include <random>


namespace Unknown
{
	class Direction {
	public:
		int x, y;
		Direction(int x, int y) : x(x), y(y) {}

		Direction operator-() {
			return Direction(-x, -y);
		}
	};

	extern Direction up;
	extern Direction down;
	extern Direction left;
	extern Direction right;

#define UP ::Unknown::Direction(0, 1)
#define DOWN ::Unknown::Direction(0, -1)
#define LEFT ::Unknown::Direction(1, 0)
#define RIGHT ::Unknown::Direction(-1, 0)

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

	template<typename T>
	class Rect {
	public:
		T x, y, w, h;
		Rect() : Rect(0, 0, 0, 0) {}
		Rect(T x, T y, T w, T h) : x(x), y(y), w(w), h(h) {}
	};

	::rapidjson::Document readJSONFile(const char* filename);

	::rapidjson::Value* getValue(const char* name, const rapidjson::Type type, rapidjson::Document& doc);

	std::shared_ptr<Colour> getColourFromString(std::string str);

	bool isCharCodeNumber(const char* key);

	std::vector<std::string> tokenise(std::string input, std::vector<std::string> extraTokens);

	long long randInt(const int min, const int max);

    bool stringToInt(const std::string& str, int& out);
}

#define RANDINT(min, max) ::Unknown::randInt(min, max)

#endif
