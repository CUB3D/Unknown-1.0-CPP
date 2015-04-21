#ifndef VECTOR_H
#define VECTOR_H

#include "Utils.h"

namespace Unknown
{
	class Vector : public Point
	{
	public:
		Vector();
		Vector(const double x, const double y);

		double getLength();

		void normalize();

		double getAngleTo(Vector vec);
	};
}

#endif