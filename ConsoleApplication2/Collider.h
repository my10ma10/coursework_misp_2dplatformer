#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

class Collider
{
public:
	Collider(Sprite& sprite);

	void Move(float dx, float dy);

	bool checkCollision(Collider other, Vector2f& directoin, float push);
	void viewCollision(Collider playerCollider);
	bool levelCollisionWithPlayer(Collider playerCollider, Vector2f levelCenter);
	void levelCollisionWithView(Collider viewCollider, Vector2f levelCenter, Vector2f tempViewCenter, View& view);
	Vector2f getPosition();
	Vector2f getHalfSize();
private:
	Sprite& sprite;
};

