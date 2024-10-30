#pragma once
#include "Entity.h"

class Object : public Entity
{
public:
	Object();
	Object(Texture* texture);
	void draw(RenderWindow& window);
	
	void setAnimation(Vector2u imageCount, float switchTime);
	void setTextureRect(const IntRect& rectangle);
	void setPosition(Vector2f position);
	void setPosition(float x, float y);

	void update(float time);
	void updateAnimation(int row, float time);
	Sprite getSprite() const;
	IntRect getCurrentRect() const;
private:
	Animation animation;
	Texture texture;
	Sprite sprite;
};


