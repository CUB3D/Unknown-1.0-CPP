#include "stdafx.h"
#include "Timer.h"

#include <SDL.h>

Unknown::Timer::Timer() : Timer(1) {}

Unknown::Timer::Timer(const float seconds) : timerSpeed(seconds * 1000) {}

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
