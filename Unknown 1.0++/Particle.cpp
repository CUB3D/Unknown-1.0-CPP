#include "stdafx.h"
#include "Particle.h"


Unknown::Graphics::Particle::Particle(Sprite* sprite, const int life) : TwoStateEntity(sprite)
{
	timer = Timer((long long)life);
}

void Unknown::Graphics::Particle::update()
{
	if (timer.isTickComplete())
	{
		kill();
	}
}
