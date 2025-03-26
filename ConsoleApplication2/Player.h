#pragma once
#include "Person.h"
#include "Object.h"
#include <functional>
#include <unordered_map>

class Player : public Person
{
public:
	Player();
	Player(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime);

	void draw(RenderWindow& window);
	void update(float time) override;

	void attack();
	void superAttack();
	void addEnemy(Enemy* enemy);
	void removeEnemy(Enemy* enemy);
	void collectCoin(Object& coin);
	void applyBonus(Object& bonus);
	void applyPotion(Object& heart);
	void jump(float time);

	const FloatRect& getAttackRange() const;
	std::vector<Enemy*> getEnemies() const;
	bool getInvulnerability();
	bool getProtection();
	Vector2f getBodySize() const;
	unsigned int getAnimCount() const;
	float getJumpHeight() const;

private:
	void attackUpdate();
	void blockUpdate();
	void updateHealth() override;
	void keyProcessing();
	void activateBonus(ObjectType type);
	void deactivateBonus(ObjectType type);
	void superAttackAnimation();
	void updateBonuses();

	float energyDelta = 15.0f;
	unsigned int coinCounter = 0;
	bool attacking = false;
	bool energyChanged = false;
	bool superAttackState = false;
	bool attackState = false;
	bool isBlocking;
	bool isJumpKeyPressed;
	bool wasJumpKeyPressed;
	bool changedRow;
	unsigned int superAttackRow = 1;
	float jumpHeight = 36.0f;
	std::vector<Enemy*> enemiesPtr;
	std::unordered_map<ObjectType, bool> bonusStates;
	Clock armorClock;
	Clock bootClock;
	Clock bubbleClock;
	float bonusDeltaTime = 10.0f;
};

