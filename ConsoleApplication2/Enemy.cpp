#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, EnemyName name, Player* player) : \
	Person(texture, position, imageCount, switchTime), attackType(0)
{
	this->name = name;
	this->player = player;
}

void Enemy::update(float time)
{
	player->getPosition().x > this->getPosition().x ? faceRight = true : faceRight = false;
	updateAnimation(time, faceRight);
	setRow(0);

	if (!faceRight)
	{
		velocity.x -= personSpeed * 200 * time;
	}
	else
	{
		velocity.x += personSpeed * 200 * time;
	}
	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (velocity.x > 0.0f)
		{
			faceRight = true;
		}
		else
		{
			faceRight = false;
		}
	}
	velocity.y += gravity * 10000 * time; // gravity
	sprite.move(velocity * time);
	setattackRange(name);

}

bool Enemy::intersects(const FloatRect& rectangel) const
{
	return attackRange.intersects(rectangel);
}

void Enemy::attack()
{
	if (getCurrentFrame() == 5)
	{
		player->takeDamage(attackPower);
	}
	// анимация атаки
}

void Enemy::setattackRange(EnemyName name)
{
	float sizeDiff = 1.5f;
	switch (name) {
		case EnemyName::Skeleton:
			attackType = 0;
			break;
		case EnemyName::Wizard:
			attackType = 1;
			break;
		case EnemyName::Tank:
			attackType = 0;
			break;
		case EnemyName::Dragon:
			attackType = 1;
			break;
		case EnemyName::Ghost:
			attackPower = 20.0f;
			attackType = 1;
			attackRange = FloatRect(Vector2f(getPosition().x - getSize().x / 2.0f * sizeDiff, \
				getPosition().y - getSize().y / 2.0f),\
				Vector2f(getSize().x * sizeDiff, getSize().y));
			break;
		case EnemyName::darkKnight:
			attackType = 0;
			break;
		default:
			std::cout << "Unknown enemy -\_/-\n";
			break;
	}
}

FloatRect Enemy::getAttackRange() const
{
	return attackRange;
}


