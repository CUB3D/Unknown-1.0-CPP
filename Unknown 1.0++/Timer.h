#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

namespace Unknown
{
		class Timer
		{
		private:
			Uint32 timerSpeed;
			Uint32 lastTime = -1;

		public:
			Timer();
			Timer(const int seconds);

			bool isTickComplete();
		};
}

#endif