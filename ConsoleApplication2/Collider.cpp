#include "Collider.h"
#include "Consts.h"
#include <iostream>

Collider::Collider(Sprite& sprite) : sprite(sprite)
{
}


void Collider::Move(float dx, float dy) {
	sprite.move(dx, dy);
}

bool Collider::checkCollision(Collider other, Vector2f& direction, float push)
{
	Vector2f otherPos = other.getPosition();
	Vector2f otherHalfSize = other.getHalfSize();
	Vector2f thisPos = getPosition();
	Vector2f thisHalfSize = getHalfSize();

	Vector2f delta(otherPos.x - thisPos.x, otherPos.y - thisPos.y);
	Vector2f intersect(abs(delta.x) - (otherHalfSize.x + thisHalfSize.x), \
					   abs(delta.y) - (otherHalfSize.y + thisHalfSize.y));

	std::cout << intersect.x << " " << intersect.y << std::endl;
	if (intersect.x < 0.0f && intersect.y < 0.0f) {
		//push
		if (intersect.x > intersect.y) { // push out by x 
			push = std::min(std::max(push, 0.0f), 1.0f);

			if (delta.x > 0.0f) { //colliding on the right 
				Move(intersect.x * (1.0f - push), 0.0f);
				other.Move(-intersect.x * push, 0.0f); 
				direction.x = 1.0f;
				direction.y = 0.0f;

			}
			else { //colliding on the left
				Move(-intersect.x * (1.0f - push), 0.0f);
				other.Move(intersect.x * push, 0.0f);
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else {// push out by y
			if (delta.y > 0.0f) {//colliding on the top
				Move(0.0f, intersect.y * (1.0f - push));
				other.Move(0.0f, -intersect.y * push);
				direction.x = 0.0f;
				direction.y = 1.0f;

			}
			else {//colliding on a bottom
				Move(0.0f, -intersect.y * (1.0f - push));
				other.Move(0.0f, intersect.y * push);
				direction.x = 0.0f;
				direction.y = -1.0f;

			}
		}
		return true;
	}
	return false;
}

void Collider::viewCollision(Collider playerCollider) {
	Vector2f playerColliderPos = playerCollider.getPosition();
	Vector2f playerColliderHalfSize = playerCollider.getHalfSize();
	Vector2f thisPos = getPosition();
	Vector2f thisHalfSize = getHalfSize();

	Vector2f delta(playerColliderPos.x - thisPos.x, playerColliderPos.y - thisPos.y);
	Vector2f intersect(thisHalfSize.x - playerColliderHalfSize.x - abs(delta.x), \
					   thisHalfSize.y - playerColliderHalfSize.y - abs(delta.y));

	if (intersect.x < 0.0f || intersect.y < 0.0f) {
		if (intersect.x < intersect.y) {
			if (delta.x > 0.0f) { //right
				Move(-intersect.x, 0.0f);
			}
			else {//left
				Move(intersect.x, 0.0f);
			}
		}
		else {
			if (delta.y > 0.0f) {//down
				Move(0.0f, -intersect.y);
			}
			else {//up
				Move(0.0f, intersect.y);
			}
		}
	}
}

bool Collider::levelCollisionWithPlayer(Collider playerCollider, Vector2f levelCenter) {
	Vector2f playerColliderPos = playerCollider.getPosition();
	Vector2f playerColliderHalfSize = playerCollider.getHalfSize();

	Vector2f levelHalfSize = Vector2f(widht / 2.0f, height / 2.0f);

	Vector2f delta(playerColliderPos.x - levelCenter.x, playerColliderPos.y - levelCenter.y);
	Vector2f intersect(levelHalfSize.x - playerColliderHalfSize.x - abs(delta.x), \
		levelHalfSize.y - playerColliderHalfSize.y - abs(delta.y));


	if (intersect.x < 0.0f || intersect.y < 0.0f) {
		if (intersect.x < intersect.y) {
			if (delta.x > 0.0f) { //right
				playerCollider.Move(intersect.x, 0.0f);
			}
			else {//left
				playerCollider.Move(-intersect.x, 0.0f);
			}
		}
		else {
			if (delta.y > 0.0f) {//down
				playerCollider.Move(0.0f, intersect.y);
			}
			else {//up
				playerCollider.Move(0.0f, -intersect.y);
			}
		}
		return true;
	}
	return false;
}

void Collider::levelCollisionWithView(Collider viewCollider, Vector2f levelCenter, Vector2f tempViewCenter, View& view) {
	Vector2f viewColliderPos = viewCollider.getPosition();
	Vector2f viewColliderHalfSize = viewCollider.getHalfSize();
	Vector2f levelHalfSize = Vector2f(widht / 2.0f, height / 2.0f);

	Vector2f delta(levelCenter.x - viewColliderPos.x, levelCenter.y - viewColliderPos.y);
	Vector2f intersect(levelHalfSize.x - (abs(delta.x) + viewColliderHalfSize.x), \
		levelHalfSize.y - (abs(delta.y) + viewColliderHalfSize.y));


	if (intersect.x < 0.0f || intersect.y < 0.0f) {
		if (intersect.x < intersect.y) {
			if (delta.x > 0.0f) { //right
				//view.move(intersect.x, 0.0f);
				view.setCenter(tempViewCenter);
			}
			else {//left
				//view.move(-intersect.x, 0.0f);
				view.setCenter(tempViewCenter);
			}
		}
		else {
			if (delta.y > 0.0f) {//down
				view.move(0.0f, intersect.y);
			}
			else {//up
				view.move(0.0f, -intersect.y);
			}
		}
	}
}

Vector2f Collider::getPosition() {
	return sprite.getPosition();
}

Vector2f Collider::getHalfSize() {
	return Vector2f(sprite.getGlobalBounds().getSize()) / 2.0f;
}


