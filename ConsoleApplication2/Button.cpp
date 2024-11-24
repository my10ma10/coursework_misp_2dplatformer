#include "Button.h"

Button::Button(std::string text, Vector2f position, Vector2f size) : isPressed(false), isHover(false)
{
	setFont("Fonts\\arial.ttf");
	this->text = Text(text, this->font);
	this->text.setPosition(position);
	Vector2f leftTopPosition(position.x - size.x / 2.0f, position.y - size.y / 2.0f);
	buttonRect = FloatRect(leftTopPosition, size);
}

void Button::setFont(std::string fontPath)
{
	if (!this->font.loadFromFile(fontPath))
	{
		std::cerr << "Can't load a font";
	}
}

void Button::setMousePosition(Vector2f mousePosition)
{

}
