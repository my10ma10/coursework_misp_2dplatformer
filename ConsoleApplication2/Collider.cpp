#include "Collider.h"

Collider::Collider() 
{
	this->sprite = nullptr;
}

Collider::Collider(Sprite& sprite) 
{
	this->sprite = &sprite;
}

void Collider::Move(float dx, float dy) {
	sprite->move(dx, dy);
}

bool Collider::externalCollider(Collider other, Vector2f& direction, float push)
{
	Vector2f otherPos = other.getPosition();
	Vector2f otherHalfSize = getHalfSize();
	Vector2f thisPos = getPosition();
	Vector2f thisHalfSize = getHalfSize();

	Vector2f delta(otherPos.x - thisPos.x, otherPos.y - thisPos.y);
	Vector2f intersect(abs(delta.x) - (otherHalfSize.x + thisHalfSize.x), \
					   abs(delta.y) - (otherHalfSize.y + thisHalfSize.y));

	if (intersect.x < 0.0f && intersect.y < 0.0f) 
	{
		//push
		if (intersect.x > intersect.y) 
		{ // push out by x 
			push = std::min(std::max(push, 0.0f), 1.0f);
			if (delta.x > 0.0f) 
			{ //colliding on the right 
				Move(intersect.x * (1.0f - push), 0.0f);
				other.Move(-intersect.x * push, 0.0f); 
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else 
			{ //colliding on the left
				Move(-intersect.x * (1.0f - push), 0.0f);
				other.Move(intersect.x * push, 0.0f);
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else 
		{// push out by y
			if (delta.y > 0.0f) 
			{//colliding on the top
				Move(0.0f, intersect.y * (1.0f - push));
				other.Move(0.0f, -intersect.y * push);
				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else 
			{//colliding on a bottom
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

void Collider::internalCollider(Collider playerCollider) 
{
	Vector2f playerColliderPos = playerCollider.getPosition();
	Vector2f playerColliderHalfSize = playerCollider.getHalfSize();
	Vector2f thisPos = getPosition();
	Vector2f thisHalfSize = getHalfSize();

	Vector2f delta(playerColliderPos.x - thisPos.x, playerColliderPos.y - thisPos.y);
	Vector2f intersect(thisHalfSize.x - playerColliderHalfSize.x - abs(delta.x), \
					   thisHalfSize.y - playerColliderHalfSize.y - abs(delta.y));

	if (intersect.x < 0.0f && intersect.y < 0.0f)
	{
		if (delta.x > 0.0f)
		{ //right
			Move(-intersect.x, 0.0f);
		}
		else
		{//left
			Move(intersect.x, 0.0f);
		}
		if (delta.y > 0.0f)
		{//down
			Move(0.0f, -intersect.y);
		}
		else
		{//up
			Move(0.0f, intersect.y);
		}
	}
	else if (intersect.x < 0.0f || intersect.y < 0.0f) 
	{
		if (intersect.x < intersect.y) 
		{
			if (delta.x > 0.0f) 
			{ //right
				Move(-intersect.x, 0.0f);
			}
			else 
			{//left
				Move(intersect.x, 0.0f);
			}
		}
		else 
		{
			if (delta.y > 0.0f) 
			{//down
				Move(0.0f, -intersect.y);
			}
			else 
			{//up
				Move(0.0f, intersect.y);
			}
		}
	}
}

bool Collider::levelCollision(Collider playerCollider, Vector2f bodySize) 
{
	Vector2f playerColliderPos = playerCollider.getPosition();
	Vector2f playerColliderHalfSize = bodySize / 2.0f;

	Vector2f levelHalfSize = Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f);

	Vector2f delta(playerColliderPos.x - levelHalfSize.x, playerColliderPos.y - levelHalfSize.y);
	Vector2f intersect(levelHalfSize.x - playerColliderHalfSize.x - abs(delta.x), \
		levelHalfSize.y - playerColliderHalfSize.y - abs(delta.y));


	if (intersect.x < 0.0f || intersect.y < 0.0f) 
	{
		if (intersect.x < intersect.y) 
		{
			if (delta.x > 0.0f) 
			{ //right
				playerCollider.Move(intersect.x, 0.0f);
			}
			else 
			{//left
				playerCollider.Move(-intersect.x, 0.0f);
			}
		}
		else 
		{
			if (delta.y > 0.0f) 
			{//down
				playerCollider.Move(0.0f, intersect.y);
			}
			else 
			{//up
				playerCollider.Move(0.0f, -intersect.y);
			}
		}
		return true;
	}
	return false;
}


Vector2f Collider::getPosition() 
{
	return sprite->getPosition();
}

Vector2f Collider::getHalfSize() 
{
	return Vector2f(sprite->getGlobalBounds().getSize()) / 2.0f;
}


