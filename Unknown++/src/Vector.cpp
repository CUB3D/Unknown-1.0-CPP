#include "stdafx.h"
#include "Vector.h"

#include <math.h>

#include "Utils.h"


Unknown::Vector::Vector()
{
	this->x = 0;
	this->y = 0;
}

Unknown::Vector::Vector(const double x, const double y)
{
	this->x = x;
	this->y = y;
}

double Unknown::Vector::getLength()
{
	return sqrt((x * x) + (y * y));
}

void Unknown::Vector::normalize()
{
	double len = getLength();

	this->x /= len;
	this->y /= len;
}

double Unknown::Vector::getAngleTo(Vector vec)
{
	return -(atan2(y - vec.y, x - vec.x) * 180 / PI) + 90;
}
