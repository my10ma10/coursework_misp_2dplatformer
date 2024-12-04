#include "Button.h"

Button::Button(std::string text, Color textColor, Vector2f size, Vector2f position) : isPressed(false), isHover(false)
{
	/*float deltaSize = 1.5f;
	setFont("Fonts\\Rubik-VariableFont_wght.ttf");
	this->text = Text("", font, 30);
	this->text.setString(text);
	this->text.setFillColor(Color::Black);

	Vector2f textCenter(this->text.getGlobalBounds().getPosition().x + this->text.getGlobalBounds().getSize().x / 2.0f, \
		this->text.getGlobalBounds().getPosition().y + this->text.getGlobalBounds().getSize().y / 2.0f);
	Vector2f leftTopPosition(position.x - size.x / 2.0f, position.y - size.y / 2.0f);

	this->shape.setTextureRect(IntRect(this->text.getLocalBounds()));
	this->shape.setPosition(textCenter);
	this->shape.setFillColor(Color::Yellow);*/
	shape.setPosition(position);
	shape.setSize(size);
	shape.setFillColor(Color::Black);

	setFont("Fonts\\Rubik-VariableFont_wght.ttf");
	this->text.setFont(font);
	this->text.setString(text);
	this->text.setCharacterSize(15);
	this->text.setFillColor(textColor);
	FloatRect textBounds = this->text.getLocalBounds();
	this->text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
	this->text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
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
}

void Button::setFont(std::string fontPath)
{
	if (!this->font.loadFromFile(fontPath))
	{
		std::cerr << "Can't load a font";
	}
}

void Button::checkMousePosition(Vector2f mousePosition)
{

}

Vector2f Button::getPosition() const
{
	return shape.getPosition();
}
