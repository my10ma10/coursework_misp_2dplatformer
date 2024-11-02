#include "Entity.h"

Entity::Entity() : life(1)
{
	speed.x = 0;
	speed.y = 0;
}

Entity::Entity(Vector2f size, Vector2f position) : Entity()
{
	body.setSize(Vector2f(size));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	sprite.setPosition(position);
}

Entity::Entity(Texture* texture, Vector2f size, Vector2f position) : Entity(size, position)
{
	body.setTexture(texture);
	sprite.setTexture(*texture);
}

//Entity::Entity(Image& image, Vector2f size, Vector2f position) : Entity(size, position)
//{
//	Texture tex;
//	if (!tex.loadFromImage(image)) {
//		std::cerr << "Failed to load PNG image." << std::endl;
//	}
//	body.setTexture(&texture);
//}

void Entity::draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Entity::setAnimation(Vector2u imageCount, float switchTime)
{
	animation = Animation(&texture, imageCount, switchTime);
}

void Entity::setTextureRect(const IntRect& rectangle)
{
	sprite.setTextureRect(rectangle);
}

void Entity::setPosition(Vector2f position)
{
	sprite.setPosition(position);
	body.setPosition(position);
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
	this->texture = texture;
}

Sprite Entity::getSprite() const
{
	return sprite;
}
