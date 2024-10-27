#pragma once
#include "Collider.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

class Person
{
public:
	Person(Texture* texture, Vector2f size, Vector2f position);
	const Texture* getTexture() const;
	RectangleShape getBody() const;
	Vector2f getPosition() const;
	Vector2f getSpeed() const;
	Collider getCollider();
	Vector2f getSize() const;

	void setSpeed(float _speedX, float _speedY);
	void setSize(Vector2f size);
	void setTexture(Texture& texture);
	void setPosition(Vector2f position);
protected:
	int widht, height;
	float speedX, speedY;
	Texture texture;
	Sprite sprite;
	RectangleShape body;
};

