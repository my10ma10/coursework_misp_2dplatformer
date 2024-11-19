#include "Person.h"

Person::Person(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime) : \
	Entity(texture, position, imageCount, switchTime), faceRight(true), attackPower(0.0f), energy(0), health(HEALTH_MAX),\
	canJump(false), isDamageTaking(false)
{
}


void Person::takeDamage(int damageAmount)
{
	health -= damageAmount;
}

void Person::update(float time)
{
}

void Person::OnCollition(Vector2f direction)
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
