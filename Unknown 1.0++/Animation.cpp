#include "Animation.h"

#include <vector>

#include <Image.h>

void Unknown::Graphics::Animation::addFrame(std::shared_ptr<Image> frame, int delayms)
{
	AnimationFrame animationFrame;

	animationFrame.frameImage = frame;
	animationFrame.delayms = delayms;

	addFrame(animationFrame);
}

void Unknown::Graphics::Animation::addFrame(AnimationFrame frame)
{
	frames.push_back(frame);
}

void Unknown::Graphics::Animation::draw(const int x, const int y)
{
	this->draw(x, y, 0);
}

void Unknown::Graphics::Animation::draw(const int x, const int y, const double angle)
{
	AnimationFrame currentFrame = frames[currentFrameIndex];

	if (!hasInit)
	{
		frameTimer.resetTimer();
		frameTimer.timerSpeed = currentFrame.delayms;
		hasInit = true;
	}

	if(currentFrame.frameImage)
		currentFrame.frameImage->render(x, y, angle);

	if (frameTimer.isTickComplete())
	{
		currentFrameIndex++;

		if ((unsigned int) currentFrameIndex == frames.size() && loop)
			currentFrameIndex = 0;

		frameTimer.timerSpeed = frames[currentFrameIndex].delayms;
	}
}

Unknown::Graphics::Animation::Animation() : currentFrameIndex(0), loop(false), done(false) {

}

void Unknown::Graphics::Animation::drawNoAdvance(const int x, const int y, const double angle) const {
	AnimationFrame currentFrame = frames[currentFrameIndex];

	if(currentFrame.frameImage)
		currentFrame.frameImage->render(x, y, angle);
}

void Unknown::Graphics::Animation::attemptAdvanceFrame() {
    if(done)
        return;

	AnimationFrame currentFrame = frames[currentFrameIndex];

	if (!hasInit)
	{
		frameTimer.resetTimer();
		frameTimer.timerSpeed = currentFrame.delayms;
		hasInit = true;
	}


	if (frameTimer.isTickComplete())
	{
		currentFrameIndex++;

		if (currentFrameIndex == frames.size() - 1) {
            if (loop) {
                currentFrameIndex = 0;
            } else {
                done = true;
            }
        }

		frameTimer.timerSpeed = frames[currentFrameIndex].delayms;
	}
}
