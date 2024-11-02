#include "Person.h"

Person::Person(Vector2f size, Vector2f position) : Entity(size, position)
{
}

Person::Person(Texture* texture, Vector2f size, Vector2f position)	: Entity(texture, size, position)
{
}

//Person::Person(Image& image, Vector2f size, Vector2f position) : Entity(image, size, position)
//{
//}
void Person::updateAnimation(int row, float time)
{
	animation.updateAnimation(row, time);
}
//void Person::setImage(std::string fileName) {
//	std::string filePath = fileName;
//	try {
//		if (!image.loadFromFile(filePath)) {
//			std::cout << "image - -\n";
//		}
//		else {
//			image.loadFromFile(filePath);
//			//image.createMaskFromColor(Color(255, 255, 255));
//			texture.loadFromImage(image);
//			sprite.setTexture(texture);
//		}
//	}
//	catch (std::string err) {
//		std::cout << "Exception error " << err.what() << std::endl;
//	}
//}


Collider Person::getCollider() {
	return Collider(body);
}

Vector2f Person::getSize() const
{
	return body.getSize();
}

const Texture* Person::getTexture() const {
	return &texture;
}

RectangleShape Person::getBody() const
{
	return body;
}

Vector2f Person::getPosition() const 
{
	return body.getPosition();
}

Vector2f Person::getSpeed() const
{
	return Vector2f(speed.x, speed.y);
}

