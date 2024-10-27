#pragma once
#include "Person.h"


class Player : public Person
{
private:
	const float speed = 0.1f;
	Vector2f velocity;
	bool canJump;
	float jumpHeight = 32.0f;
	const float gravity = 0.001f;
public:
	Player(Texture* texture, Vector2f size, Vector2f position);
	void update(float time);
	//void handleInput(Event event);
	void OnCollition(Vector2f direction);
	Vector2f getOrigin() const;
	
	Vector2f getVelocity() const;
};

