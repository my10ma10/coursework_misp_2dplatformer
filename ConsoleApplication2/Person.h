#pragma once
#include "Entity.h"

class Person : public Entity
{
public:
	Person();
	Person(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime);

	virtual void takeDamage(int damageAmount);
	virtual void updateHealth() = 0;
	void onCollition();

	void setAttackPower(float power);
	void setSpeed(float speed);

	unsigned int getCurrentFrame() const;
	Vector2f& getDirection();
	Vector2f getOrigin() const;
	Vector2f getVelocity() const;
	float getEnergy() const;
	int getHealth() const;
	bool getFaceRight() const;

protected:
	int health;
	float energy;
	float attackPower;
	bool faceRight;
	bool canAttack;
	bool canJump;
	bool isDamageTaking;
	bool killing;
	Vector2f direction;
	Vector2f velocity;
	float speed;
	float gravity = 0.001f;
	FloatRect attackRange;
};

class Enemy;
enum class EnemyName { Basic, Skeleton, Wizard, Tank, Dragon, Ghost, DarkKnight };
