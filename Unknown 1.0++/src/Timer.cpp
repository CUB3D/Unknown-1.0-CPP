#include "Timer.h"

#include <Unknown.h>
#include "core/hook/HookRegistry.h"
#include "core/hook/Event.h"

Unknown::Timer::Timer() : Timer((float)1) {}

Unknown::Timer::Timer(const float seconds) : timerSpeed(seconds * 1000) {}

Unknown::Timer::Timer(const long long speed) : timerSpeed(speed) {}

bool Unknown::Timer::isTickComplete()
{
	if (lastTime == -1) {
		resetTimer();
	}

	if (SDL_GetTicks() >= this->lastTime + this->timerSpeed) {
		resetTimer();

		if(this->callback) {
			callback();
		}

		return true;
	}

	return false;
}

void Unknown::Timer::resetTimer()
{
	this->lastTime = SDL_GetTicks();
}

Unknown::Timer::Timer(const long long speed,
					  std::function<void(void)> callback) : timerSpeed(speed), callback(callback) {

    HookRegistry<UpdateEvent>::getInstance().add([=]{this->isTickComplete();});
}

Unknown::Timer::Timer(const float speed,
					  std::function<void(void)> callback) : timerSpeed(speed * 1000), callback(callback){
    HookRegistry<UpdateEvent>::getInstance().add([=]{this->isTickComplete();});
}
