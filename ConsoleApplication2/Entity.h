#pragma once
#include "Consts.h"
#include "Collider.h"
#include "Animation.h"
#include <iostream>

class Entity
{
public:
	Entity();
	Entity(Vector2f position);
	Entity(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime);

	virtual void update(float time) = 0;
	void updateAnimation(float time, bool faceRight);

	virtual void draw(RenderWindow& window);

	void setAnimation(Vector2u imageCount, float switchTime);
	void setTextureRect(const IntRect& rectangle);
	void setPosition(Vector2f position);
	void setPosition(float x, float y);
	void setSpeed(Vector2f speed);
	void setSpeed(float speedX, float speedY);
	void setTexture(Texture& texture);
	void setRow(unsigned int row);

	Collider getCollider();
	IntRect getCurrentRect() const;
	bool getLife() const;
	Vector2f getPosition() const;
	Vector2f getSize() const;
	Vector2f getSpeed() const;
	Sprite& getSprite();
	const Texture* getTexture() const;

protected:
	std::string name;
	Vector2f speed;
	Animation animation;
	Texture sheetTexture;
	Sprite sprite;
	Texture spriteTexture;
	bool life;
	unsigned int row;


};

