#ifndef SPRITE_H
#define SPRITE_H

#include "Unknown.h"
#include "Image.h"
#include "Vector.h"
#include "Utils.h"
#include "Physics.h"
#include "Animation.h"

namespace Unknown
{
	class Sprite
	{
	private:
		double angle;

	public:
		Point<int> location;
		Vector direction;
		mutable AABB bounds;

		Sprite(const int x, const int y);
		virtual ~Sprite();

		virtual void render() const;

		void setAngle(double angle);
		double getAngle() const;

		void move(const int speedX, const int speedY);

		virtual Sprite* clone() const;
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

			virtual Sprite* clone() const;
		};

		class AnimatedSprite : public Sprite
		{
		public:
			Animation* animation;

			AnimatedSprite(const int x, const int y, Animation* animation);
			virtual ~AnimatedSprite();
			virtual void render() const;
			virtual Sprite* clone() const;
		};
	}
}

#endif

