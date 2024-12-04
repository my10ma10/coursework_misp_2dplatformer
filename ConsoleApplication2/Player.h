#pragma once
#include "Person.h"
#include "Object.h"

class Player : public Person
{
public:
	Player(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime);

	void draw(RenderWindow& window);
	void update(float time) override;
	void attackUpdate();
	void blockUpdate();

	void attack();
	void superAttack();
	void superAttackAnimation();
	void addEnemy(Enemy* enemy);
	void removeEnemy(Enemy* enemy);
	void collectCoin(Object& coin);
	void applyBonus(Object& bonus);
	void applyHeart(Object& heart);
	void jump(float time);
	void updateBonuses();

	std::vector<Enemy*> getEnemies() const;
	Vector2f getSize() const;
	unsigned int getAnimCount() const;
	float getJumpHeight() const;

private:
	float energyDelta = 15.0f;
	unsigned int coinCounter = 0;
	bool attacking = false;
	bool energyChanged = false;
	bool superAttackState = false;
	bool attackState = false;
	bool isBlocking;
	bool bubbleBonusState;
	bool isJumpKeyPressed;
	bool wasJumpKeyPressed;
	bool changedRow;
	unsigned int superAttackRow = 1;
	float jumpHeight = 36.0f;
	Texture bubbleTexture;
	Sprite bubble;
	std::vector<Enemy*> enemiesPtr; // 
};

