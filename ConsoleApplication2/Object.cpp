#include "Object.h"

Object::Object()
{
}

Object::Object(Texture* texture) : texture(*texture)
{
}

void Object::draw(RenderWindow& window)
{
	window.draw(sprite);
}

void Object::setAnimation(Vector2u imageCount, float switchTime)
{
	animation = Animation(&texture, imageCount, switchTime);
}

void Object::setTextureRect(const IntRect& rectangle)
{
	sprite.setTextureRect(rectangle);
}

void Object::updateAnimation(int row, float time)
{
	animation.updateAnimation(row, time);
}

Sprite Object::getSprite() const
{
	return sprite;
}
