#ifndef VECTOR_H
#define VECTOR_H

#include "Utils.h"
#include <Box2D/Box2D.h>
#include <rttr/registration.h>

namespace Unknown {
	class Vector {
	public:
        double x;
        double y;

		Vector();
		Vector(const double x, const double y);
		Vector(const b2Vec2 vec);

		double getLength() const;

		Vector normalize() const;

		double getAngleTo(Vector vec) const;

		Vector operator+(Vector other) const;
		Vector operator*(double other) const;

        operator b2Vec2() const;

        b2Vec2 getBox2DVec() const;
	};
}

#endif