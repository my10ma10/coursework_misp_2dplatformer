#include "Object.h"

Object::Object() : Entity()
{
}

Object::Object(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime) : Entity(texture, position, imageCount, switchTime)
{
	Vector2f textureSize(texture->getSize().x, texture->getSize().y);
	//sprite.setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));
	this->sheetTexture = Texture(*texture);
}


void Object::update(float time)
{
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