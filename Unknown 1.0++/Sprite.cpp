#include "stdafx.h"
#include "Sprite.h"

#include "Unknown.h"
#include "Image.h"
#include "Vector.h"

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

double Unknown::Sprite::getAngle()
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
	this->image->render(this->location.x, this->location.y);
}

