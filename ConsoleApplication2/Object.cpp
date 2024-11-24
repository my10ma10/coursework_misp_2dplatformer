#include "Object.h"

Object::Object() : Entity()
{
}

Object::Object(Texture* sheetTexture, Vector2f position, Vector2u imageCount, \
	float switchTime, Vector2f size) : Entity(sheetTexture, position, size, imageCount, switchTime)
{
	Vector2f textureSize(sheetTexture->getSize());
	this->sheetTexture = Texture(*sheetTexture);

}

void Object::update(float time)
{
}

void Object::draw(RenderWindow& window)
{
	Image image;
	window.draw(sprite);
	window.draw(bonusIconSprite);
}

void Object::setBonusIconSprite(std::string& path)
{
	if (!bonusIconTexture.loadFromFile(path))
	{
		std::cerr << "Can't load an image";
	}
	bonusIconSprite.setTexture(bonusIconTexture);
}