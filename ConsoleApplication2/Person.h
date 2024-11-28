#pragma once
#include "Entity.h"

class Person : public Entity
{
public:
	Person();
	Person(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime);

	void takeDamage(int amount);
	void updateHealth();
	void onCollition();

	void setAttackPower(float power);
	void setSpeed(float speed);

	unsigned int getCurrentFrame() const;
	Vector2f& getDirection();
	Vector2f getOrigin() const;
	Vector2f getVelocity() const;
	int getHealth() const;

protected:
	int health;
	int energy;
	float attackPower;
	bool faceRight;
	bool canAttack;
	bool canJump;
	bool isDamageTaking;

	Vector2f direction;
	Vector2f velocity;
	float personSpeed = 1.0f;
	float gravity = 0.001f;
};

class Enemy;
enum class EnemyName { Basic, Skeleton, Wizard, Tank, Dragon, Ghost, darkKnight };
