#pragma once
#include "Person.h"
#include "Object.h"

class Player : public Person
{
public:
	Player(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime);

	void draw(RenderWindow& window);

	void attack(Enemy& enemy);
	void superattack(Enemy& enemy);
	void collectCoin(Object& coin);
	void applyBonus(Object& bonus);
	void applyHeart(Object& heart);
	void update(float time) override;
	void jump();

	Vector2f getSize() const;
	unsigned int getAnimCount() const;

private:
	bool isBlocking;
	bool blockBonus;
	bool isJumpKeyPressed;
	bool wasJumpKeyPressed;
	float jumpHeight = 36.0f;
	Texture bubbleTexture;
	Sprite bubble;
};

