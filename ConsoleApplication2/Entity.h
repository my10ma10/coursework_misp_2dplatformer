#pragma once
#include "Collider.h"
#include "Animation.h"
#include <iostream>

class Entity
{
public:
	Entity();
	Entity(Vector2f size, Vector2f position);
	Entity(Texture* texture, Vector2f size, Vector2f position);
	virtual void update(float time) = 0;

	void setSpeed(float _speedX, float _speedY);
	void setTexture(Texture& texture);
	void setPosition(Vector2f position);
protected:
	float speedX, speedY;
	Texture texture;
	RectangleShape body;
	bool life;

};

