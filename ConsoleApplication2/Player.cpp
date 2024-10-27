#include "Player.h"

Player::Player(Texture* texture, Vector2f size, Vector2f position): Person(texture, size, position), canJump(false) {}

void Player::update(float time)
{
	velocity.x = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		velocity.x -= speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		velocity.x += speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::W) && canJump) {
		canJump = false;
		velocity.y = -sqrtf(2.0f * gravity * jumpHeight);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		
	}
	velocity.y += gravity * time; // gravity
	body.move(velocity * time);
}

void Player::OnCollition(Vector2f direction)
{
	if (direction.x < 0.0f) { // collition on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f) { // collition on the right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f) { // collition on the bottom
		velocity.y = 0.0f;
		canJump = true;
	}
	else if (direction.y > 0.0f) { // collition on the top
		velocity.y = 0.0f;
	}
}

Vector2f Player::getOrigin() const
{
	return body.getOrigin();
}

Vector2f Player::getVelocity() const
{
	return velocity;
}

