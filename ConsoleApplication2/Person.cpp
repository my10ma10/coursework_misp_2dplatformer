#include "Person.h"

Person::Person(Texture* texture, Vector2f size, Vector2f position) :
	widht(widht), height(height), speedX(0), speedY(0)
{
	body.setSize(Vector2f(size));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
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

void Person::setSize(Vector2f size) {
	widht = size.x;
	height = size.y;
}


void Person::setTexture(Texture& texture)
{
	texture = texture;
}

void Person::setPosition(Vector2f position)
{
	body.setPosition(position);
}

//void Person::setDirection(int direction)
//{
//	dir = direction;
//}

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
	return Vector2f(speedX, speedY);
}

void Person::setSpeed(float _speedX, float _speedY)
{
	speedX = _speedX;
	speedY = _speedY;
}
