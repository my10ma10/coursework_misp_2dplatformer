#pragma once
#include "Person.h"
#include "Player.h"


enum class EnemyName {Skeleton, Wizard, Tank, Dragon, Ghost, darkKnight};

class Enemy : public Person
{
public:
	Enemy();
	Enemy(Vector2f position);
	Enemy(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, EnemyName name);

	void update(float time);
	void attack(Player& player);
	void setattackRange(EnemyName name);
	//анимация атаки
	//анимация смерти
	//

private:
	EnemyName name;
	bool attackRange; // 0 - ближний, 1 - дальний
};

