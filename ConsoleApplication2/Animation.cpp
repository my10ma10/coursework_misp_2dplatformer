#include "Animation.h"

Animation::Animation(): \
	imageCount(Vector2u(0,0)), switchTime(0.0f), totalTime(0.0f), isNewRow(0)
{
}

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) : \
	imageCount(imageCount), switchTime(switchTime), totalTime(0.0f), isNewRow(0)
{
	currentFrame.x = 0;
	currentRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
	currentRect.height = texture->getSize().y / static_cast<float>(imageCount.y);

}

void Animation::updateAnimation(int row, float time, bool faceRight)
{
	isLoopDone = false;
	currentFrame.y = row;
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
	if (currentFrame.x == 8)
	{
		isLoopDone = true;
	}
	if (isNewRow)
	{
		currentFrame.x = 0;
		isNewRow = false;
	}
}

IntRect Animation::getCurrentRect() const
{
	return currentRect;
}

unsigned int Animation::getCurrentFrame() const
{
	return currentFrame.x;
}

void Animation::changeRow()
{
	isNewRow = true;
	

}
