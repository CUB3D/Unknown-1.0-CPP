#include "stdafx.h"
#include "Sprite.h"

#include "Unknown.h"
#include "Image.h"
#include "Vector.h"
#include "Utils.h"

#include <Math.h>

// Sprite class

Unknown::Sprite::Sprite(const int x, const int y)
{
	this->location.x = x;
	this->location.y = y;

	this->bounds.location.x = x;
	this->bounds.location.y = y;

	this->direction = Vector(0, 0);

	this->setAngle(0);
}

Unknown::Sprite::~Sprite()
{
}

void Unknown::Sprite::render() const
{
	//NOOP
}


void Unknown::Sprite::setAngle(double angle)
{
	this->angle = angle;

	direction.x = cos((PI * angle) / 180);
	direction.y = sin((PI * angle) / 180);

	if (direction.getLength() > 0)
		direction.normalize();
}

double Unknown::Sprite::getAngle() const
{
	return this->angle;
}

void Unknown::Sprite::move(const int speedX, const int speedY)
{
	Vector velocity = Vector(direction.x * speedX, direction.y * speedY);

	this->location.x += velocity.x;
	this->location.y += velocity.y;

	this->bounds.location.x = this->location.x;
	this->bounds.location.y = this->location.y;
}

Unknown::Sprite* Unknown::Sprite::clone() const
{
	Sprite* returnValue = (Sprite*)malloc(sizeof Sprite);
	memcpy(returnValue, this, sizeof *this);
	return returnValue;
}

// ImageSprite class

Unknown::Graphics::ImageSprite::ImageSprite(const int x, const int y, Image* image) : Sprite(x, y)
{
	this->image = image;

	this->bounds.size.width = image->textureRect.w;
	this->bounds.size.height = image->textureRect.h;
}

Unknown::Graphics::ImageSprite::~ImageSprite()
{
}

void Unknown::Graphics::ImageSprite::render() const
{
	this->image->render(this->location.x, this->location.y, getAngle());
}

Unknown::Sprite* Unknown::Graphics::ImageSprite::clone() const
{
	Sprite* returnValue = (Sprite*)malloc(sizeof ImageSprite);
	memcpy(returnValue, this, sizeof *this);
	return returnValue;
}

// AnimatedSprite class

Unknown::Graphics::AnimatedSprite::AnimatedSprite(const int x, const int y, Animation* animation) : Sprite(x, y)
{
	this->animation = animation;

	AnimationFrame frame = this->animation->frames[this->animation->currentFrameIndex];
	
	this->bounds.size.width = frame.frameImage->textureRect.w;
	this->bounds.size.height = frame.frameImage->textureRect.h;
}

Unknown::Graphics::AnimatedSprite::~AnimatedSprite()
{
	// NOOP
}

void Unknown::Graphics::AnimatedSprite::render() const
{
	this->animation->draw(this->location.x, this->location.y, this->getAngle());

	AnimationFrame frame = this->animation->frames[this->animation->currentFrameIndex];

	this->bounds.size.width = frame.frameImage->textureRect.w;
	this->bounds.size.height = frame.frameImage->textureRect.h;
}

Unknown::Sprite* Unknown::Graphics::AnimatedSprite::clone() const
{
	Sprite* ret = (Sprite*)malloc(sizeof AnimatedSprite);
	memcpy(ret, this, sizeof *this);
	return ret;
}
