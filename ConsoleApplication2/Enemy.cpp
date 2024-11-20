#include "Enemy.h"

Enemy::Enemy(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, EnemyName name, Player* player) : \
	Person(texture, position, imageCount, switchTime), attackType(0)
{
	this->name = name;
	this->player = player;
	personSpeed = 12500.0f;
}

void Enemy::update(float time)
{
	player->getPosition().x > this->getPosition().x ? faceRight = true : faceRight = false;
	updateAnimation(time / 1.5f, faceRight);
	if (moveRangeIntersect(FloatRect(player->getPosition() - player->getSize() / 2.0f, player->getSize())))
	{
		if (!faceRight)
		{
			velocity.x = -personSpeed * time;
		}
		else if (faceRight)
		{
			velocity.x = personSpeed * time;
		}
	}
	else
	{
		velocity.x = 0.0f;
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
	if (velocity.x > personSpeed)
	{
		velocity.x = personSpeed;
	}
	if (velocity.x < -personSpeed)
	{
		velocity.x = -personSpeed;
	}
	velocity.y += gravity * 10000 * time; // gravity
	sprite.move(velocity * time);
	setRanges(name);
}

bool Enemy::attackRangeIntersect(const FloatRect& rectangel) const
{
	return attackRange.intersects(rectangel);
}

bool Enemy::moveRangeIntersect(const FloatRect& rectangel) const
{
	return moveRange.intersects(rectangel);
}

void Enemy::attack()
{
	row = 2;
	if (getCurrentFrame() == 5 and !isDamageTaking)
	{
		isDamageTaking = true;
		player->takeDamage(attackPower);
	}
	if (getCurrentFrame() != 5)
	{
		isDamageTaking = false;
	}
	// анимация атаки
}

void Enemy::setRanges(EnemyName name)
{
	float attackSizeDiff = 2.0f; // разница между размером спрайта и области атаки
	float moveSizeDiff = 3.0f; // разница между размером спрайта и области движения к игроку
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

			attackRange = FloatRect(Vector2f(getPosition().x - getSize().x / 2.0f * attackSizeDiff, \
				getPosition().y - getSize().y / 2.0f), \
				Vector2f(getSize().x * attackSizeDiff, getSize().y));
			moveRange = FloatRect(Vector2f(getPosition().x - getSize().x / 2.0f * moveSizeDiff, \
				getPosition().y - getSize().y / 2.0f), \
				Vector2f(getSize().x * moveSizeDiff, getSize().y));
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


