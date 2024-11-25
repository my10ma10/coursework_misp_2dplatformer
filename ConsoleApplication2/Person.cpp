#include "Person.h"

Person::Person(Texture* texture, Vector2f position, Vector2f size, Vector2u imageCount, float switchTime) : \
	Entity(texture, position, size, imageCount, switchTime), faceRight(true), attackPower(0.0f), energy(0), \
	health(HEALTH_MAX),	canJump(false), isDamageTaking(false), direction(0.0f, 0.0f)
{
}

void Person::takeDamage(int damageAmount)
{
	health -= damageAmount;
}

void Person::onCollition()
{
	if (direction.x < 0.0f)
	{ // collition on the left
		velocity.x = 0.0f;
		canJump = false;
	}
	else if (direction.x > 0.0f)
	{ // collition on the right
		velocity.x = 0.0f;
		canJump = false;
	}
	if (direction.y < 0.0f)
	{ // collition on the bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{ // collition on the top
		velocity.y = 0.0f;
		canJump = false;
	}
	if (direction.x != 0.0f)
	{
		canJump = false;
	}
}

unsigned int Person::getCurrentFrame() const
{
	return animation.getCurrentFrame();
}

Vector2f& Person::getDirection()
{
	return direction;
}

Vector2f Person::getOrigin() const
{
	return sprite.getOrigin();
}

Vector2f Person::getVelocity() const
{
	return velocity;
}

int Person::getHealth() const
{
	return health;
}
