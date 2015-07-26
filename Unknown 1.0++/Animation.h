#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "Image.h"
#include "Timer.h"

namespace Unknown
{
	namespace Graphics
	{
		struct AnimationFrame
		{
			Image* frameImage;
			int delayms;
		};

		class Animation
		{
		private:
			Timer frameTimer;
			bool hasInit = false;

		public:
			std::vector<AnimationFrame> frames;
			int currentFrameIndex = 0;

			void addFrame(Image* frame, const int delayms);
			void addFrame(AnimationFrame frame);
			void draw(const int x, const int y);
		};
	}
}

#endif