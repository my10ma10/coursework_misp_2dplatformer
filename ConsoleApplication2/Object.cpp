#include "Object.h"

Object::Object() : Entity()
{
}

Object::Object(Texture* texture, Vector2f size, Vector2f position) : Entity(texture, size, position)
{
	Vector2f textureSize(texture->getSize().x, texture->getSize().y);
	sprite.setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));
	this->texture = Texture(*texture);
}


void Object::update(float time)
{
}

void Object::updateAnimation(int row, float time)
{
	animation.updateAnimation(row, time);
	std::cout << this->sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
}

Sprite Object::getSprite() const
{
	return sprite;
}

IntRect Object::getCurrentRect() const
{
	return animation.getCurrentRect();
}

//static Object createObject(std::string path)
//{
//	Texture texture;
//	Object object;
//	if (texture.loadFromFile("Image\\coin-Sheet.png")) {
//		object = Object(&texture, Vector2f(0, 0), Vector2f(0, 0));
//	}
//	return object;
//}