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
	//Entity(Image& image, Vector2f size, Vector2f position);
	//virtual void update(float time) = 0;

	//void superattack(&атакуемый враг)
	void draw(RenderWindow& window);

	void setAnimation(Vector2u imageCount, float switchTime);
	void setTextureRect(const IntRect& rectangle);
	void setPosition(Vector2f position);
	void setPosition(float x, float y);
	void setSpeed(Vector2f speed);
	void setSpeed(float speedX, float speedY);
	void setTexture(Texture& texture);

	Sprite getSprite() const;
protected:
	std::string name;
	Vector2f speed;
	Animation animation;
	Texture texture;
	Sprite sprite;
	RectangleShape body;
	bool life;


};

