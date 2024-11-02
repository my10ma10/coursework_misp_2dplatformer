#pragma once
#include "Person.h"


class Player : public Person
{
public:
	Player(Vector2f size, Vector2f position);
	Player(Texture* texture, Vector2f size, Vector2f position);
	//Player(Image& image, Vector2f size, Vector2f position);
	void update(float time);
	void OnCollition(Vector2f direction);
	void draw(RenderWindow& window);

	Vector2f getOrigin() const;
	Vector2f getVelocity() const;

private:
	const float speed = 0.1f;
	Vector2f velocity;
	bool canJump;
	float jumpHeight = 32.0f;
	const float gravity = 0.001f;
};

