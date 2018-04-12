#ifndef VECTOR_H
#define VECTOR_H

#include "Utils.h"

namespace Unknown
{
	class Vector
	{
	public:
        double x;
        double y;

		Vector();
		Vector(const double x, const double y);

		double getLength() const;

		Vector normalize() const;

		double getAngleTo(Vector vec) const;

		Vector operator+(Vector other) const;
		Vector operator*(double other) const;
	};
}

#endif