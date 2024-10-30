#include "Entity.h"

Entity::Entity() : speedX(0), speedY(0), life(1)
{

}

Entity::Entity(Vector2f size, Vector2f position) : Entity()
{
	body.setSize(Vector2f(size));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
}

Entity::Entity(Texture* texture, Vector2f size, Vector2f position) : Entity(size, position)
{
	body.setTexture(texture);
}

void Entity::setTexture(Texture& texture)
{
	texture = texture;
}

void Entity::setPosition(Vector2f position)
{
	body.setPosition(position);
}

void Entity::setSpeed(float _speedX, float _speedY)
{
	speedX = _speedX;
	speedY = _speedY;
}
