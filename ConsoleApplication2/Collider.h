#pragma once
#include "SFML\Graphics.hpp"
using namespace sf;

class Collider
{
public:
	Collider(RectangleShape& body);

	void Move(float dx, float dy);

	bool checkCollision(Collider other, Vector2f& directoin, float push);
	void viewCollision(Collider playerCollider);
	void levelCollision(Collider playerCollider, Vector2f levelCenter, Vector2f& direction);
	Vector2f getPosition();
	Vector2f getHalfSize();
private:
	RectangleShape& body;
};

