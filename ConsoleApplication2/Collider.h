#pragma once
#include "SFML\Graphics.hpp"
#include "Consts.h"

using namespace sf;

class Collider
{
public:
	Collider(Sprite& sprite);

	void Move(float dx, float dy);

	bool externalCollider(Collider other, Vector2f& directoin, Vector2f bodySize, float push = 1.0f);
	void internalCollider(Collider playerCollider);
	bool levelCollision(Collider playerCollider, Vector2f bodySize);
	//not used
	void levelCollisionWithView(Collider viewCollider, Vector2f levelCenter, Vector2f tempViewCenter, View& view);

	Vector2f getPosition();
	Vector2f getHalfSize();
private:
	Sprite& sprite;
};

