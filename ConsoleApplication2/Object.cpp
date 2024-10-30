#include "Object.h"

Object::Object()
{
}

Object::Object(Texture* texture) : texture(*texture)
{
	Vector2f textureSize(texture->getSize().x, texture->getSize().y);
	sprite.setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));
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

void Object::setPosition(Vector2f position)
{
	sprite.setPosition(position);
}

void Object::setPosition(float x, float y)
{
	sprite.setPosition(x, y);
}

void Object::updateAnimation(int row, float time)
{
	animation.updateAnimation(row, time);
}

Sprite Object::getSprite() const
{
	return sprite;
}

IntRect Object::getCurrentRect() const
{
	return animation.getCurrentRect();
}

static Object createObject(std::string path)
{
	Texture texture;
	Object object;
	if (texture.loadFromFile("Image\\coin-Sheet.png")) {
		object = Object(&texture);
	}
	return object;
}