#pragma once
#include "Person.h"
#include "Player.h"

class Enemy : public Person
{
public:
	Enemy();
	Enemy(Vector2f position);
	Enemy(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, std::string name);

	void update(float time);
	void attack(Player& player);
	//анимация атаки
	//анимация смерти
	//

private:
	std::string name;
	bool attackRange; // 0 - ближний, 1 - дальний
};

