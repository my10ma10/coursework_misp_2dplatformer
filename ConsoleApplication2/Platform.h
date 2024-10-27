#pragma once
#include "SFML\Graphics.hpp"
#include "Collider.h"

class Platform
{
public:
	Platform(Texture* texture, Vector2f size, Vector2f position);
	Platform(Vector2f size, Vector2f position);

	RectangleShape getBody() const;
	void draw(RenderWindow& window);
	Collider getCollider();
private:
	RectangleShape body;
};

