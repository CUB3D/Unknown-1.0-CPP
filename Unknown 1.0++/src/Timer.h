#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
#include <functional>

namespace Unknown
{
		class Timer
		{
		private:
			long long lastTime = -1;
			std::function<void(void)> callback;

		public:
			long long timerSpeed;

			Timer();

			explicit Timer(const float seconds);
			explicit Timer(const long long speed);

			explicit Timer(const long long speed, std::function<void(void)> callback);
			explicit Timer(const float speed, std::function<void(void)> callback);

			bool isTickComplete();
			void resetTimer();
		};
}

#endif