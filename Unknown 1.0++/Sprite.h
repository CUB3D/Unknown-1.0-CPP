#ifndef SPRITE_H
#define SPRITE_H

#include "Unknown.h"
#include "Image.h"
#include "Vector.h"
#include "Utils.h"
#include "Physics.h"

namespace Unknown
{
	class Sprite
	{
	private:
		double angle;

	public:
		Point location;
		Vector direction;
		AABB bounds;

		Sprite(const int x, const int y);
		virtual ~Sprite();

		virtual void render() const;

		void setAngle(double angle);
		double getAngle();

		void move(const int speedX, const int speedY);
	};

	namespace Graphics
	{
		class ImageSprite : public Sprite
		{
		public:
			Image* image;

			ImageSprite(const int x, const int y, Image* image);
			virtual ~ImageSprite();

			virtual void render() const;
		};
	}
}

#endif

