#include "stdafx.h"
#include "Animation.h"

#include <vector>

#include "Image.h"

void Unknown::Graphics::Animation::addFrame(Unknown::Graphics::Image* frame, int delayms)
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

	currentFrame.frameImage->render(x, y, angle);

	if (frameTimer.isTickComplete())
	{
		currentFrameIndex++;

		if (currentFrameIndex == frames.size())
		{
			currentFrameIndex = 0;
		}

		frameTimer.timerSpeed = frames[currentFrameIndex].delayms;
	}
}
