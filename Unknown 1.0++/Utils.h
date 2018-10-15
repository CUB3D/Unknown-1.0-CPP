#ifndef UTILS_H
#define UTILS_H

#define PI 3.141592653589793238462

#include "Colour.h"
#include "document.h"
#include <vector>
#include <memory>
#include <random>
#include <SDL.h>


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

		Dimension(T t1, T t2) : width(t1), height(t2){}
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

		Rect<int> operator *(int value) {
			return Rect<int>(x * value, y * value, w * value, h * value);
		}

		Rect<int> operator /(int value) {
			return Rect<int>(x / value, y / value, w / value, h / value);
		}

		template<typename R>
		bool contains(Rect<R> other) {
			return !(other.x + other.w < x || other.x > x + w || other.y + other.h < y || other.y > y + h);
		}

		Point<T> center() {
		    return Point<T>(x + w / 2, y + h / 2);
		}

		template<typename R>
		bool contains(Point<R> t) {
			bool X = t.x > x && t.x < x + w;
			bool Y = t.y > y && t.y < y + h;

			return X && Y;
		}

	};

	::rapidjson::Document readJSONFile(const char* filename);

	::rapidjson::Value* getValue(const char* name, const rapidjson::Type type, rapidjson::Document& doc);

	std::shared_ptr<Colour> getColourFromString(std::string str);

	bool isCharCodeNumber(const char* key);
	bool isStringNumerical(const std::string& str);

	std::vector<std::string> tokenise(std::string input, std::vector<std::string> extraTokens);

	long long randInt(const int min, const int max);

    bool stringToInt(const std::string& str, int& out);
    std::string intToString(const int x);
}

#define RANDINT(min, max) ::Unknown::randInt(min, max)

#endif
