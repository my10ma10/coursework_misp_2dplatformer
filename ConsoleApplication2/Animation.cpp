#include "Animation.h"

Animation::Animation(): \
	imageCount(Vector2u(0,0)), switchTime(0.0f), totalTime(0.0f), isLoopDone(false)
{
}

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) : \
	imageCount(imageCount), switchTime(switchTime), totalTime(0.0f), isLoopDone(false)
{
	currentFrame.x = 0;
	currentRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
	currentRect.height = texture->getSize().y / static_cast<float>(imageCount.y);

}

bool Animation::updateAnimation(int row, float time, bool faceRight)
{
	if (currentFrame.y != row) 
	{
		currentFrame.y = row;
		currentFrame.x = 0;
	}
	if (currentFrame.x == imageCount.x - 1)
	{
		isLoopDone = true;

	}
	else
	{
		isLoopDone = false;
	}
	totalTime += time;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentFrame.x++;
		if (currentFrame.x >= imageCount.x)
		{
			currentFrame.x = 0;
		}
	}
	currentRect.top = currentFrame.y * currentRect.height;

	if (faceRight)
	{
		currentRect.left = currentFrame.x * currentRect.width;
		currentRect.width = abs(currentRect.width);
	}
	else
	{
		currentRect.left = (currentFrame.x + 1) * abs(currentRect.width);
		currentRect.width = -abs(currentRect.width);
	}
	if (isLoopDone and row == 3)
	{
		return true;
	}
	return false;
}

IntRect Animation::getCurrentRect() const
{
	return currentRect;
}

unsigned int Animation::getCurrentFrame() const
{
	return currentFrame.x;
}
