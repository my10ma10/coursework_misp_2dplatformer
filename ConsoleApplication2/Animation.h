#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Animation
{
public:
	Animation();
	Animation(Texture* texture, Vector2u imageCount, float switchTime);
	void updateAnimation(int row, float time, bool faceRight);

	IntRect getCurrentRect() const;
	unsigned int getCurrentFrame() const;
	void changeRow();

private:
	IntRect currentRect;
	Vector2u currentFrame;
	Vector2u imageCount;
	float totalTime;
	float switchTime;
	bool isNewRow;
};

