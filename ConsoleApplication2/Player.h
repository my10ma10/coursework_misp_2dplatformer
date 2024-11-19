#pragma once
#include "Person.h"
#include "Object.h"

class Player : public Person
{
public:
	Player(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime);

	void attack(Enemy& enemy);
	void superattack(Enemy& enemy);
	void collectCoin(Object& coin);
	void applyBonus(Object& bonus);
	void applyHeart(Object& heart);
	void update(float time) override;
	Vector2f getSize() const;


private:
	bool isBlocking;
	float jumpHeight = 44.0f;
};

