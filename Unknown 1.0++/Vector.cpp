#include "stdafx.h"
#include "Vector.h"

#include <math.h>

#include "Utils.h"


Unknown::Vector::Vector() : Vector(0, 0) {}

Unknown::Vector::Vector(const double x, const double y) : x(x), y(y) {}

double Unknown::Vector::getLength() const
{
	return sqrt((x * x) + (y * y));
}

Unknown::Vector Unknown::Vector::normalize() const
{
	double len = getLength();

    Unknown::Vector newVector(this->x / len, this->y / len);

    return newVector;
}

double Unknown::Vector::getAngleTo(Vector vec) const
{
	return -(atan2(y - vec.y, x - vec.x) * 180 / PI) + 90;
}

Unknown::Vector Unknown::Vector::operator+(Unknown::Vector other) const
{
	return Unknown::Vector(this->x + other.x, this->y + other.y);
}

Unknown::Vector Unknown::Vector::operator*(double other) const
{
	return Unknown::Vector(this->x * other, this->y * other);
}

Unknown::Vector::operator b2Vec2() const {
    return b2Vec2(this->x, this->y);
}

Unknown::Vector::Vector(const b2Vec2 vec) : Vector(vec.x, vec.y) {}

b2Vec2 Unknown::Vector::getBox2DVec() const {
    return b2Vec2(this->x, this->y);
}
