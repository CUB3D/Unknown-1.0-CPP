#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

namespace Unknown
{
		class Timer
		{
		private:
			Uint32 lastTime = -1;

		public:
			Uint32 timerSpeed;

			Timer();
			Timer(const float seconds);

			bool isTickComplete();
			void resetTimer();
		};
}

#endif