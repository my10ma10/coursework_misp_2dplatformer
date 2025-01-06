#include "Button.h"

Button::Button(std::string text, Color textColor, Color shapeColor, const Font& font, Vector2f size, Vector2f position)\
	: isPressed(false), isHover(false), isClickable(true), font(font)
{
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(shapeColor);

	setFont("Fonts\\Rubik-VariableFont_wght.ttf");
	this->text.setCharacterSize(24);
	this->text.setFillColor(textColor);
	this->text.setString(text);
	this->text.setFont(font);

	FloatRect textBounds = this->text.getLocalBounds();
	this->text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
	this->text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f );
}

Button::Button(const wchar_t* text, Color textColor, Color shapeColor, const Font& font, Vector2f size, Vector2f position)\
	: isPressed(false), isHover(false), isClickable(true), font(font)
{
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(shapeColor);

	setFont("Fonts\\Rubik-VariableFont_wght.ttf");
	this->text.setCharacterSize(24);
	this->text.setFillColor(textColor);
	this->text.setString(text);
	this->text.setFont(font);

	FloatRect textBounds = this->text.getLocalBounds();
	this->text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
	this->text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

void Button::draw(RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}

void Button::update(Vector2i mousePos, bool isButtonPressed)
{
	mousePosition = mousePos;
	if (isClickable) 
	{
		if (shape.getGlobalBounds().contains(Vector2f(mousePosition)))
		{
			isHover = true;
			if (isButtonPressed)
			{
				isPressed = true;
			}
			else
			{
				isPressed = false;
			}
		}
		else
		{
			isHover = false;
			isPressed = false;
		}
	}
}

void Button::setClickable(bool pred)
{
	isClickable = pred;
}

void Button::setPressed(bool pred)
{
	isPressed = pred;
}

void Button::setFont(const std::string& fontPath)
{
	if (!font.loadFromFile(fontPath)) 
	{
		std::cerr << "Cannot load font\n";
	}
}

void Button::setShapeColor(Color color)
{
	shape.setFillColor(color);
}


Vector2f Button::getPosition() const
{
	return shape.getPosition();
}

Text Button::getText() const
{
	return text;
}

bool Button::getPressed() const
{
	return isPressed;
}
