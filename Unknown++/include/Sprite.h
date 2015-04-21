#ifndef SPRITE_H
#define SPRITE_H

#include "Unknown.h"
#include "Image.h"
#include "Vector.h"
#include "Utils.h"

namespace Unknown
{
	class Sprite
	{
	private:
		double angle;

	public:
		Point location;
		Vector direction;

		Sprite(const int x, const int y);

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

			virtual void render() const;

			ImageSprite(const int x, const int y, Image* image);
		};
	}
}

#endif

