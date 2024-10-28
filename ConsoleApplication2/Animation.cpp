#include "Animation.h"

Animation::Animation(): \
	imageCount(Vector2u(0,0)), switchTime(0.0f), totalTime(0.0f)
{
}

Animation::Animation(Texture* texture, Vector2u imageCount, float switchTime) : \
	imageCount(imageCount), switchTime(switchTime), totalTime(0.0f)
{
	currentImage.x = 0;
	currentRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
	currentRect.height = texture->getSize().y / static_cast<float>(imageCount.y);

}

void Animation::updateAnimation(int row, float time)
{
	currentImage.y = row;
	totalTime += time;
	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0;
		}
	}
	currentRect.left = currentImage.x * currentRect.width;
	currentRect.top = currentImage.y * currentRect.height;
}

IntRect Animation::getCurrentRect() const
{
	return currentRect;
}
