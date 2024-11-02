#pragma once
#include "Entity.h"

class Object : public Entity
{
public:
	Object();
	Object(Texture* newtexture, Vector2f size, Vector2f position);

	void update(float time);
	void updateAnimation(int row, float time);
	Sprite getSprite() const;
	IntRect getCurrentRect() const;
private:
};


