#pragma once
#include "Person.h"
#include "Player.h"


enum class EnemyName {Skeleton, Wizard, Tank, Dragon, Ghost, darkKnight};

class Enemy : public Person
{
public:
	Enemy(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, EnemyName name, Player* player);

	void update(float time);
	bool intersects(const FloatRect& rectangel) const;
	void attack();
	void setattackRange(EnemyName name);
	//анимация атаки
	//анимация смерти
	//
	FloatRect getAttackRange() const;
	unsigned int getCurrentFrame() const;

private:
	EnemyName name;
	bool attackType; // 0 - ближний, 1 - дальний
	Player* player = nullptr;
	FloatRect attackRange;
};

