#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "Image.h"
#include "Timer.h"

namespace Unknown {

	struct AnimationFrame {
		std::shared_ptr<Image> frameImage;
		int delayms;
	};

	class Animation {
	private:
		Timer frameTimer;
		bool hasInit = false;
		bool done;

	public:
		std::vector<AnimationFrame> frames;
		int currentFrameIndex = 0;
		bool loop;

		Animation();

		void addFrame(std::shared_ptr<Image> frame, int delayms);
		void addFrame(AnimationFrame frame);

		void draw(const int x, const int y, const double angle);
		void draw(const int x, const int y);

		void drawNoAdvance(const int x, const int y, const double angle) const;
		void attemptAdvanceFrame();
	};
}

#endif