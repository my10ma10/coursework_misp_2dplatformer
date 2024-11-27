#include "Enemy.h"

Enemy::Enemy() : attackType(0), name(EnemyName::Basic)
{
}

Enemy::Enemy(Texture* texture, Vector2f position, Vector2u imageCount, \
	float switchTime, EnemyName name, Player* playerPtr, Vector2f size) : \
	Person(texture, position, size, imageCount, switchTime), attackType(0)
{
	this->name = name;
	this->playerPtr = playerPtr;
	personSpeed = 1500.0f;
}

void Enemy::update(float time)
{
	playerPtr->getPosition().x > this->getPosition().x ? faceRight = true : faceRight = false;
	updateAnimation(time / 1.5f, faceRight);
	;

	if (moveRangeIntersect(FloatRect(playerPtr->getPosition() - playerPtr->getSize() / 2.0f, playerPtr->getSize())))
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
	initEnemy(name);
}

bool Enemy::attackRangeIntersect(const FloatRect& rectangel) const
{
	return attackRange.intersects(rectangel);
}

bool Enemy::moveRangeIntersect(const FloatRect& rectangel) const
{
	return moveRange.intersects(rectangel);
}

void Enemy::stoppingRect(const FloatRect& rectangel)
{
	if (this->sprite.getGlobalBounds().intersects(rectangel))
	{
		velocity.x = 0.0f;
	}
}

void Enemy::attack()
{
	row = 2;
	if (getCurrentFrame() == 5 and !isDamageTaking)
	{
		isDamageTaking = true;
		playerPtr->takeDamage(attackPower);
	}
	if (getCurrentFrame() != 5)
	{
		isDamageTaking = false;
	}
}

void Enemy::initEnemy(EnemyName name)
{
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
			setAttackMoveRange(6.0f, 12.0f);
			break;
		case EnemyName::darkKnight:
			attackPower = 40.0f;
			attackType = 0;

			break;
		default:
			std::cout << "Unknown enemy -\_/-\n";
			break;
	}
}

void Enemy::setAttackMoveRange(float attackSizeDiff, float moveSizeDiff)
{
	attackRange = FloatRect(Vector2f(getPosition().x - getSize().x / 2.0f * attackSizeDiff, \
		getPosition().y - getSize().y / 2.0f), \
		Vector2f(getSize().x * attackSizeDiff, getSize().y));
	attackRange.top -= playerPtr->getJumpHeight();
	attackRange.height += playerPtr->getJumpHeight();

	moveRange = FloatRect(Vector2f(getPosition().x - getSize().x / 2.0f * moveSizeDiff, \
		getPosition().y - getSize().y / 2.0f), \
		Vector2f(getSize().x * moveSizeDiff, getSize().y));
	moveRange.top -= playerPtr->getJumpHeight();
	moveRange.height += playerPtr->getJumpHeight();

}

FloatRect Enemy::getAttackRange() const
{
	return attackRange;
}



