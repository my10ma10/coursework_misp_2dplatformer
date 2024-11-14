#include "Entity.h"

Entity::Entity() : life(1), row(0), speed(0, 0)
{
}

Entity::Entity(Vector2f position) : Entity()
{
	sprite.setPosition(position);
}

Entity::Entity(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime) : Entity(position)
{
	sprite.setTexture(*texture);
	this->sheetTexture = *texture;
	Vector2f spriteSheetSize(sheetTexture.getSize());

	sprite.setOrigin(spriteSheetSize.x / (imageCount.x * 2.0f), spriteSheetSize.y / (imageCount.y * 2.0f));
	setAnimation(imageCount, switchTime);
}

void Entity::updateAnimation(float time, bool faceRight)
{
	setTextureRect(this->getCurrentRect());
	animation.updateAnimation(this->row, time, faceRight);
}

void Entity::draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Entity::setAnimation(Vector2u imageCount, float switchTime)
{
	animation = Animation(&sheetTexture, imageCount, switchTime);
}

void Entity::setTextureRect(const IntRect& rectangle)
{
	sprite.setTextureRect(rectangle);
}

void Entity::setPosition(Vector2f position)
{
	sprite.setPosition(position);
}

void Entity::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Entity::setSpeed(Vector2f speed)
{
	this->speed = Vector2f(speed);
}

void Entity::setSpeed(float speedX, float speedY)
{
	speed.x = speedX;
	speed.y = speedY;
}

void Entity::setTexture(Texture& texture)
{
	this->sheetTexture = texture;
}

void Entity::setRow(unsigned int row)
{
	this->row = row;
}

Sprite& Entity::getSprite()
{
	return sprite;
}

const Texture* Entity::getTexture() const
{
	return &sheetTexture;;
}

Collider Entity::getCollider()
{
	return Collider(sprite);
}

IntRect Entity::getCurrentRect() const
{
	return animation.getCurrentRect();
}

bool Entity::getLife() const
{
	return life;
}

Vector2f Entity::getPosition() const
{
	return sprite.getPosition();
}

Vector2f Entity::getSize() const
{
	return sprite.getGlobalBounds().getSize();
}

Vector2f Entity::getSpeed() const
{
	return speed;
}
