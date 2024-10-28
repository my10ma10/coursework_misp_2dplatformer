#pragma once
#include "Collider.h"
#include "Animation.h"
#include <iostream>


class Person
{
public:
	Person(Vector2f size, Vector2f position);
	Person(Texture* texture, Vector2f size, Vector2f position);
	const Texture* getTexture() const;
	RectangleShape getBody() const;
	Vector2f getPosition() const;
	Vector2f getSpeed() const;
	Collider getCollider();
	Vector2f getSize() const;

	void setSpeed(float _speedX, float _speedY);
	void setTexture(Texture& texture);
	void setPosition(Vector2f position);
protected:
	float speedX, speedY;
	Texture texture;
	RectangleShape body;
};

