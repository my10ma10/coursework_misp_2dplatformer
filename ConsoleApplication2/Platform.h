#pragma once
#include "SFML\Graphics.hpp"
#include "Collider.h"

class Platform
{
public:
	Platform(Vector2f size, Vector2f position);
	Platform(Texture* texture, Vector2f size, Vector2f position);

	void draw(RenderWindow& window);
	Collider getCollider();
	Sprite& getSprite();

private:
	Sprite sprite;
	Texture texture;
};

