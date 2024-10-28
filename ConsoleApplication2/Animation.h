#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Animation
{
public:
	Animation();
	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	void updateAnimation(int row, float time);

	IntRect getCurrentRect() const;

private:
	IntRect currentRect;
	Vector2u currentImage;
	Vector2u imageCount;
	float totalTime;
	float switchTime;
};

