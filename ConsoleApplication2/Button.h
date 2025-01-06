#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>

using namespace sf;

class Button
{
public:
	Button(std::string text, Color textColor, Color shapeColor, const Font& font, Vector2f size = Vector2f(0.0f, 0.0f), \
		Vector2f position = Vector2f(0.0f, 0.0f));
	Button(const wchar_t* text, Color textColor, Color shapeColor, const Font& font, Vector2f size = Vector2f(0.0f, 0.0f), \
		Vector2f position = Vector2f(0.0f, 0.0f));
	void draw(RenderWindow& window);
	void update(Vector2i mousePos, bool isButtonPressed);

	void setClickable(bool pred);
	void setPressed(bool pred);
	void setFont(const std::string& fontPath);
	void setShapeColor(Color color);

	Vector2f getPosition() const;
	Text getText() const;
	bool getPressed() const;

private:
	

	RectangleShape shape;
	Text text;
	Font font;
	Vector2f buttonPosition;
	Vector2i mousePosition;
	bool isPressed;
	bool isHover;
	bool isClickable;
};

