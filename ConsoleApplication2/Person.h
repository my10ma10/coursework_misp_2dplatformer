#pragma once
#include "Entity.h"

class Person : public Entity
{
public:
	Person();
	Person(Vector2f position);
	Person(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime);


	//void updateAnimation(int row, float time, bool faceRight);
	void takeDamage(int amount);
	void update(float time) override;

	Vector2f getOrigin() const;
	Vector2f getVelocity() const;
	int getHealth() const;

protected:
	int health;
	int energy;
	int attackPower;
	bool faceRight;

	Vector2f velocity;
	const float personSpeed = 0.1f;
	const float gravity = 0.001f;
};

class Enemy;