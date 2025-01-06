#include "Object.h"

Object::Object() : Entity()
{
	this->objectType = objectType;
}

Object::Object(Texture* sheetTexture, Vector2f position, Vector2u imageCount, float switchTime, \
	ObjectType objectType, Vector2f bodySize) : 
		Entity(sheetTexture, position, bodySize, imageCount, switchTime)
{
	this->sheetTexture = Texture(*sheetTexture);
	this->objectType = objectType;
}

void Object::update(float time)
{
	updateAnimation(time, true);
}

void Object::draw(RenderWindow& window)
{
	if (life)
	{
		window.draw(sprite);
		window.draw(bonusIconSprite);
	}
}

void Object::setBonusIconSprite(std::string& path)
{
	if (!bonusIconTexture.loadFromFile(path))
	{
		std::cerr << "Can't load an image";
	}
	bonusIconSprite.setTexture(bonusIconTexture);
}

ObjectType Object::getType() const
{
	return objectType;
}
