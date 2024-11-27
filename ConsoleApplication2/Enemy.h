#pragma once
#include "Person.h"
#include "Player.h"


class Enemy : public Person
{
public:
	Enemy();
	Enemy(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, EnemyName name, \
		Player* playerPtr = nullptr, Vector2f size = Vector2f(16.0f, 16.0f));
	void update(float time);
	void changeRanges();
	bool attackRangeIntersect(const FloatRect& rectangel) const;
	bool moveRangeIntersect(const FloatRect& rectangel) const;
	bool stopRangeIntersect(const FloatRect& rectangel) const;
	void stoppingRect(const FloatRect& rectangel);
	void attack();
	void initEnemy(EnemyName name);
	void setAttackMoveStopRange(float attackSizeDiff, float moveSizeDiff);
	FloatRect getAttackRange() const;

private:
	EnemyName name;
	bool attackType; // 0 - ближний, 1 - дальний
	Player* playerPtr = nullptr;
	FloatRect attackRange;
	FloatRect moveRange;
	FloatRect stopRange;
};

