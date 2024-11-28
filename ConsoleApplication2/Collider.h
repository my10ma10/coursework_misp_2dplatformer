#pragma once
#include "SFML\Graphics.hpp"
#include "Consts.h"

using namespace sf;

class Collider
{
public:
	Collider(Sprite& sprite);

	void Move(float dx, float dy);

	bool externalCollider(Collider other, Vector2f& directoin, float push = 1.0f);
	void internalCollider(Collider playerCollider);
	bool levelCollision(Collider playerCollider, Vector2f bodySize);

	Vector2f getPosition();
	Vector2f getHalfSize();
private:
	Sprite& sprite;
};

