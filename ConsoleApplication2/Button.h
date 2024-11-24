#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>


using namespace sf;

class Button
{
public:
	Button(std::string text, Vector2f position = Vector2f(0.0f, 0.0f), Vector2f size = Vector2f(0.0f, 0.0f));
	void setFont(std::string fontPath);
	void setMousePosition(Vector2f mousePosition);

private:
	Text text;
	Font font;
	Vector2f buttonPosition;
	Vector2f mousePosition;
	FloatRect buttonRect;
	bool isPressed;
	bool isHover;
};

