#include "Object.h"

Object::Object() : Entity()
{
}

Object::Object(Texture* sheetTexture, Vector2f position, Vector2u imageCount, float switchTime) : Entity(sheetTexture, position, imageCount, switchTime)
{
	Vector2f textureSize(sheetTexture->getSize().x, sheetTexture->getSize().y);
	this->sheetTexture = Texture(*sheetTexture);

}

Object::~Object()
{
	delete bonusIconTexture;
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
	if (!bonusIconTexture->loadFromFile(path))
	{
		std::cerr << "Can't load an image";
	}
	bonusIconSprite.setTexture(*bonusIconTexture);
}





//static Object createObject(std::string path)
//{
//	Texture* texture;
//	Object object;
//	if (texture->loadFromFile("Image\\coin-Sheet.png")) {
//		object = Object(texture, Vector2f(0, 0), Vector2u(0, 0), 0.0f);
//	}
//	return object;
//}