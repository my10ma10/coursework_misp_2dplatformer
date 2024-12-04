#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;

class Bar
{
public:
	Bar(Vector2f size, Vector2f position, Color color, int amount);
	void update(int amount, Vector2f position);
	void draw(RenderWindow& window);

	void initcurrentAmountShape(Vector2f position, Vector2f size);
	void initFillShape(Vector2f position, Vector2f size);

private:
	RectangleShape currentAmountShape;
	Color color;
	RectangleShape fillShape;
	Vector2f size;
	int amount;
};

