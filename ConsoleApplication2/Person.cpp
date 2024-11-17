#include "Person.h"

Person::Person() : Entity(), \
	faceRight(true), attackPower(0), energy(0), health(HEALTH_MAX)
{
}

Person::Person(Vector2f position) : Entity(position), \
	faceRight(true), attackPower(0), energy(0), health(HEALTH_MAX)
{
}

Person::Person(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime) : \
	Entity(texture, position, imageCount, switchTime), faceRight(true), attackPower(0), energy(0), health(HEALTH_MAX)
{
}


void Person::takeDamage(int damageAmount)
{
	health -= damageAmount;
}

void Person::update(float time)
{
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
