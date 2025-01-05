#include "Enemy.h"

Enemy::Enemy() : attackType(0), name(EnemyName::Basic)
{
}

Enemy::Enemy(Texture* texture, Vector2f position, Vector2u imageCount, \
	float switchTime, EnemyName name, Player* playerPtr, Vector2f size) : \
	Person(texture, position, size, imageCount, switchTime), attackType(0)
{
	this->health = HealthMax / 100;
	this->name = name;
	this->playerPtr = playerPtr;
	initEnemy(name);

}

void Enemy::update(float time)
{
	updateHealth();
	playerPtr->getPosition().x > this->getPosition().x ? faceRight = true : faceRight = false;
	updateAnimation(time / 1.5f, faceRight);
	body.setPosition(getPosition());

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
	if (stopRangeIntersect(FloatRect(playerPtr->getPosition() - playerPtr->getSize() / 2.0f, playerPtr->getSize())))
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
	changeRanges();
	if (!life)
	{
		attackPower = 0.0f;
	}
}

void Enemy::updateHealth()
{
	if (health <= 0 and life)
	{
		row = 3;
		if (getCurrentFrame() == 1)
		{
			killing = true;
		}
		if (getCurrentFrame() == 0 and killing)
		{
			life = false;
		}
	}
	health = std::max(0, health);
}

void Enemy::changeRanges()
{
	switch (name) 
	{
		case EnemyName::Skeleton:
			setAttackMoveStopRange(4.0f, 15.0f);
			attackPower = 5.0f;
			break;
		case EnemyName::Wizard:
			setAttackMoveStopRange(8.0f, 11.0f);
			attackPower = 15.0f;
			break;
		case EnemyName::Tank:
			setAttackMoveStopRange(2.0f, 11.0f);
			attackPower = 10.0f;
			break;
		case EnemyName::Dragon:
			setAttackMoveStopRange(4.0f, 8.0f);
			attackPower = 13.0f;
			break;
		case EnemyName::Ghost:
			setAttackMoveStopRange(9.0f, 12.0f);
			attackPower = 15.0f;
			break;
		case EnemyName::DarkKnight:
			setAttackMoveStopRange(3.0f, 15.0f);
			attackPower = 20.0f;
			break;
		default:
			std::cout << "Unknown enemy -\_/-\n";
			break;
	}
}

bool Enemy::attackRangeIntersect(const FloatRect& rectangel) const
{
	return attackRange.intersects(rectangel);
}

bool Enemy::moveRangeIntersect(const FloatRect& rectangel) const
{
	return moveRange.intersects(rectangel);
}

bool Enemy::stopRangeIntersect(const FloatRect& rectangel) const
{
	return stopRange.intersects(rectangel);
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
		if (this->getSprite().getGlobalBounds().intersects(playerPtr->getBody().getGlobalBounds()))
		{
			playerPtr->takeDamage(attackPower);
		}
	}
	if (getCurrentFrame() != 5)
	{
		isDamageTaking = false;
	}
}

void Enemy::initEnemy(EnemyName name)
{
	switch (name) 
	{
		case EnemyName::Skeleton:
			attackType = 0;
			personSpeed = SkeletonSpeed;
			gravity = 0.003f;
			break;
		case EnemyName::Wizard:
			attackType = 1;
			personSpeed = WizardSpeed;
			gravity = 0.002f;
			break;
		case EnemyName::Tank:
			attackType = 0;
			personSpeed = TankSpeed;
			gravity = 0.005f;
			break;
		case EnemyName::Dragon:
			attackType = 1;
			personSpeed = DragonSpeed;
			gravity = 0.002f;
			health = HealthMax * 50 / 100;
			break;
		case EnemyName::Ghost:
			attackType = 1;
			personSpeed = GhostSpeed;
			gravity = 0.001f;
			health = HealthMax * 50 / 100;
			break;
		case EnemyName::DarkKnight:
			attackType = 0;
			personSpeed = DarkKnightSpeed;
			gravity = 0.005f;
			health = HealthMax * 50 / 100;
			break;
		default:
			std::cout << "Unknown enemy -\_/-\n";
			break;
	}
}

void Enemy::setAttackMoveStopRange(float attackSizeDiff, float moveSizeDiff)
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

	stopRange = FloatRect(\
		Vector2f(getPosition().x - getSpriteSize().x / 2.0f, getPosition().y - getSpriteSize().y / 2.0f), getSpriteSize());
	stopRange.top -= playerPtr->getJumpHeight();
	stopRange.height += playerPtr->getJumpHeight();
}

FloatRect Enemy::getAttackRange() const
{
	return attackRange;
}

const EnemyName& Enemy::getName() const
{
	return name;
}



