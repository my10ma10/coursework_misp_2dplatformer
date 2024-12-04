#include "Bar.h"

Bar::Bar(Vector2f size, Vector2f position, Color color, int amount) \
	: color(color), amount(amount), size(size)
{
	initcurrentAmountShape(position, size);
	initFillShape(position, size);
}

void Bar::update(int amount, Vector2f position)
{
	currentAmountShape.setSize(Vector2f(amount * size.x / this->amount, currentAmountShape.getSize().y));
	fillShape.setPosition(position);
	currentAmountShape.setPosition(position);
}

void Bar::draw(RenderWindow& window)
{
	window.draw(fillShape);
	window.draw(currentAmountShape);
}

void Bar::initcurrentAmountShape(Vector2f position, Vector2f size)
{
	currentAmountShape = RectangleShape(size);
	currentAmountShape.setPosition(position);
	currentAmountShape.setFillColor(color);
}

void Bar::initFillShape(Vector2f position, Vector2f size)
{
	fillShape = RectangleShape(size);
	fillShape.setPosition(position);
	fillShape.setFillColor(Color::White);
}
