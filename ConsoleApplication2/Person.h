#pragma once
#include "Entity.h"

class Person : public Entity
{
public:
	Person();
	Person(Vector2f position);
	Person(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime);


	void updateAnimation(int row, float time, bool faceRight);
	void takeDamage(int amount);
	void update(float time) override;

	Vector2f getOrigin() const;
	Vector2f getVelocity() const;

protected:
	int health;
	int energy;
	int attackPower;
	bool faceRight;

	const float personSpeed = 0.1f;
	Vector2f velocity;
	const float gravity = 0.001f;
};

class Enemy;