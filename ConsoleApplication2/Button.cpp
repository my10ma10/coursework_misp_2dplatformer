#include "Button.h"

Button::Button(std::string text, Vector2f position, Vector2f size) : isPressed(false), isHover(false)
{
	float deltaSize = 1.5f;
	setFont("Fonts\\Rubik-VariableFont_wght.ttf");
	this->text = Text("", font, 30);
	this->text.setString(text);
	this->text.setFillColor(Color::Black);

	Vector2f textCenter(this->text.getGlobalBounds().getPosition().x + this->text.getGlobalBounds().getSize().x / 2.0f, \
		this->text.getGlobalBounds().getPosition().y + this->text.getGlobalBounds().getSize().y / 2.0f);
	Vector2f leftTopPosition(position.x - size.x / 2.0f, position.y - size.y / 2.0f);
	this->buttonRect = IntRect(this->text.getLocalBounds());

	this->button.setTextureRect(buttonRect);
	this->button.setPosition(textCenter);
	this->button.setSize(Vector2f(buttonRect.getSize()) * deltaSize);
	this->button.setFillColor(Color::White);
	
}

void Button::draw(RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

void Button::setFont(std::string fontPath)
{
	if (!this->font.loadFromFile(fontPath))
	{
		std::cerr << "Can't load a font";
	}
	font.setSmooth(false);
}

void Button::checkMousePosition(Vector2f mousePosition)
{

}

Vector2f Button::getPosition() const
{
	return button.getPosition();
}
