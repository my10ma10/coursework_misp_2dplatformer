#pragma once
#include "Person.h"
#include "Object.h"

class Player : public Person
{
public:
	Player();
	Player(Vector2f position);
	Player(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime);
	//Player(Image& image, Vector2f size, Vector2f position);

	void attack(Enemy& enemy);
	void collectCoin(Object& coin);
	void applyBonus(Object& bonus);
	void applyHeart(Object& heart);
	void update(float time);

	void OnCollition(Vector2f direction);

private:
	const float gravity = 0.001f;
	bool canJump;
	bool isBlocking;
	float jumpHeight = 32.0f;
};

