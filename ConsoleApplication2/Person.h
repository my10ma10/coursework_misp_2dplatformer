#pragma once
#include "Entity.h"

class Person : public Entity
{
public:
	Person(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime);


	void takeDamage(int amount);
	void update(float time) override;
	void OnCollition(Vector2f direction);

	Vector2f getOrigin() const;
	Vector2f getVelocity() const;
	int getHealth() const;

protected:
	int health;
	int energy;
	int attackPower;
	bool faceRight;
	bool canJump;

	Vector2f velocity;
	const float personSpeed = 0.1f;
	const float gravity = 0.001f;
};

class Enemy;