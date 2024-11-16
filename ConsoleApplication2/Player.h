#pragma once
#include "Person.h"
#include "Object.h"

class Player : public Person
{
public:
	Player();
	Player(Vector2f position);
	Player(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime);

	void attack(Enemy& enemy);
	//void superattack(&атакуемый враг)
	void collectCoin(Object& coin);
	void applyBonus(Object& bonus);
	void applyHeart(Object& heart);
	void update(float time);

	void OnCollition(Vector2f direction);

private:
	bool canJump;
	bool isBlocking;
	float jumpHeight = 32.0f;
};

