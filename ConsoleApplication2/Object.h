#pragma once
#include "Animation.h"
#include <iostream>

class Object
{
private:
	Animation animation;
	Texture texture;
	Sprite sprite;
public:
	Object();
	Object(Texture* texture);
	void draw(RenderWindow& window);
	
	void setAnimation(Vector2u imageCount, float switchTime);
	void setTextureRect(const IntRect& rectangle);
	void setPosition(Vector2f position);
	void setPosition(float x, float y);

	void updateAnimation(int row, float time);
	Sprite getSprite() const;
	IntRect getCurrentRect() const;
};


