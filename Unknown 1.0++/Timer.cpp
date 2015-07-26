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
	{
		resetTimer();
	}

	if (SDL_GetTicks() >= this->lastTime + this->timerSpeed)
	{
		resetTimer();
		return true;
	}

	return false;
}

void Unknown::Timer::resetTimer()
{
	this->lastTime = SDL_GetTicks();
}
