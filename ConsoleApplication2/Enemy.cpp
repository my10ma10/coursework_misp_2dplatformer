#include "Enemy.h"

Enemy::Enemy() : Person()
{
}

Enemy::Enemy(Vector2f position) : Person(position)
{
}

Enemy::Enemy(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, EnemyName name) : \
	Person(texture, position, imageCount, switchTime)
{
	this->name = name;
	setattackRange(name);
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

void Enemy::setattackRange(EnemyName name)
{
	switch (name) {
		case EnemyName::Skeleton:

			break;
		case EnemyName::Wizard:
			break;
		case EnemyName::Tank:
			break;
		case EnemyName::Dragon:
			break;
		case EnemyName::Ghost:
			break;
		case EnemyName::darkKnight:
			break;
		default:
			std::cout << "Unknown enemy -\_/-\n";
			break;
	}

}
