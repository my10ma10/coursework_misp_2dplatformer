#include "Enemy.h"

Enemy::Enemy() : Person()
{
}

Enemy::Enemy(Vector2f position) : Person(position)
{
}

Enemy::Enemy(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, std::string name) : \
	Person(texture, position, imageCount, switchTime)
{
	this->name = name;
}

void Enemy::update(float time)
{
	if (faceRight) 
	{

	}
}

void Enemy::attack(Player& player)
{
	player.takeDamage(attackPower);
	// анимация атаки
}
