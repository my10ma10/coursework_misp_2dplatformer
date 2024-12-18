#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

using namespace sf;

class Button
{
public:
	Button(std::string text, Color textColor, Vector2f size = Vector2f(0.0f, 0.0f), \
		Vector2f position = Vector2f(0.0f, 0.0f));
	void draw(RenderWindow& window);
	void update(Vector2i mousePos);
	void setFont(std::string fontPath);
	void checkMousePosition(Vector2f mousePosition);

	Vector2f getPosition() const;
	Text getText() const;
	bool isClicked() const;

private:
	RectangleShape shape;
	Text text;
	Font font;
	Vector2f buttonPosition;
	Vector2i mousePosition;
	bool isPressed;
	bool isHover;
};

