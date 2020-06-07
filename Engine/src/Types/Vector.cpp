
#include "Vector.h"

#include <math.h>

#include <Utils.h>


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
	return -(atan2(y - vec.y, x - vec.x) * 180 / UK_PI) + 90;
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

bool Unknown::Vector::operator==(const Unknown::Vector &vec) const {
    return vec.x == this->x && vec.y == this->y;
}

#include <glm/glm.hpp>

RTTR_REGISTRATION {
	rttr::registration::class_<Unknown::Vector>("Vector")
	    .constructor()
	    .method("getLength", &Unknown::Vector::getLength)
	    .method("normalize", &Unknown::Vector::normalize)
	    .method("getAngleTo", &Unknown::Vector::getAngleTo)
	    .method("getBox2DVec", &Unknown::Vector::getBox2DVec)
	    .property("x", &Unknown::Vector::x)
	    .property("y", &Unknown::Vector::y);

    rttr::registration::class_<glm::vec2>("glm::vec2")
            .constructor<>()
            .property("Width", &glm::vec2::x)
            .property("x", &glm::vec2::x)
            .property("Height", &glm::vec2::y)
            .property("y", &glm::vec2::y);
};
