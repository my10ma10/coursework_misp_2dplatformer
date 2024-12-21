#include "Button.h"

Button::Button(std::string text, Color textColor, const Font& font, Vector2f size, Vector2f position) : \
	isPressed(false), isHover(false), font(font)
{
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(Color::Black);

	setFont("Fonts\\Rubik-VariableFont_wght.ttf");
	this->text.setCharacterSize(24);
	this->text.setFillColor(textColor);
	this->text.setString(text);
	this->text.setFont(font);

	FloatRect textBounds = this->text.getLocalBounds();
	this->text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
	this->text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f );
}

void Button::draw(RenderWindow& window)
{
	window.draw(shape);
	window.draw(text);
}

void Button::update(Vector2i mousePos)
{
	mousePosition = mousePos;
	if (shape.getGlobalBounds().contains(Vector2f(mousePosition)))
	{
		isHover = true;
		if (Mouse::isButtonPressed(Mouse::Button::Left))
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
	}
	std::cout << isHover << std::endl;
}

void Button::setFont(const std::string& fontPath)
{
	if (!font.loadFromFile(fontPath)) 
	{
		std::cerr << "Cannot load font\n";
	}
}

void Button::checkMousePosition(Vector2f mousePosition)
{

}

Vector2f Button::getPosition() const
{
	return shape.getPosition();
}

Text Button::getText() const
{
	return text;
}

bool Button::isClicked() const
{
	return isPressed;
}
