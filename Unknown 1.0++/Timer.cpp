#include "stdafx.h"
#include "Timer.h"

#include <SDL.h>

Unknown::Timer::Timer()
{
	this->timerSpeed = 1000;
}

Unknown::Timer::Timer(const int seconds)
{
	this->timerSpeed = 1000 * seconds;
}

bool Unknown::Timer::isTickComplete()
{
	if (lastTime == -1)
		this->lastTime = SDL_GetTicks();

	if (SDL_GetTicks() > this->lastTime + this->timerSpeed)
	{
		this->lastTime = SDL_GetTicks();
		return true;
	}

	return false;
}
