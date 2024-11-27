#include "Entity.h"

Entity::Entity() : life(true), row(0)
{
}

Entity::Entity(Vector2f position) : Entity()
{
	sprite.setPosition(position);
}

Entity::Entity(Texture* texture, Vector2f position, Vector2f bodySize, Vector2u imageCount, float switchTime) : \
	life(true), row(0)
{
	this->sheetTexture = *texture;
	sprite.setPosition(position);
	sprite.setTexture(*texture);
	Vector2f spriteSheetSize(sheetTexture.getSize());
	sprite.setOrigin(spriteSheetSize.x / (imageCount.x * 2.0f), spriteSheetSize.y / (imageCount.y * 2.0f));
	sprite.setTextureRect(IntRect(Vector2i(getPosition()),
		Vector2i(getSize().x / imageCount.x, getSize().y / imageCount.y)));

	body.setPosition(position);
	body.setTextureRect(IntRect(Vector2i(position - bodySize / 2.0f), Vector2i(bodySize)));



	setAnimation(imageCount, switchTime);
}

bool Entity::updateAnimation(float time, bool faceRight)
{
	setTextureRect(this->getCurrentRect());
	if (animation.updateAnimation(this->row, time, faceRight))
	{
		return true;
	}
	return false;
}

void Entity::draw(RenderWindow& window)
{
	if (life)
	{
		window.draw(sprite);
	}
}

void Entity::kill()
{
	life = false;
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

Sprite Entity::getBody() const
{
	return body;
}

Collider Entity::getBodyCollider()
{
	return Collider(body);
}

Collider Entity::getSpriteCollider()
{
	return Collider(sprite);
}

IntRect Entity::getCurrentRect() const
{
	return animation.getCurrentRect();
}

bool Entity::alive() const
{
	return life;
}

Vector2f Entity::getPosition() const
{
	return sprite.getPosition();
}

Vector2f Entity::getSize() const
{
	return body.getGlobalBounds().getSize();
}

Vector2f Entity::getSpriteSize() const
{
	return sprite.getGlobalBounds().getSize();
}
