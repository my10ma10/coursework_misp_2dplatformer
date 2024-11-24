#pragma once
#include "Entity.h"

class Person : public Entity
{
public:
	Person(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime);


	void takeDamage(int amount);
	void OnCollition(Vector2f direction);

	unsigned int getCurrentFrame() const;
	Vector2f getOrigin() const;
	Vector2f getVelocity() const;
	int getHealth() const;

protected:
	int health;
	int energy;
	float attackPower;
	bool faceRight;
	bool canJump;
	bool isDamageTaking;

	Vector2f velocity;
	float personSpeed = 1.0f;
	float gravity = 0.001f;
};

class Enemy;