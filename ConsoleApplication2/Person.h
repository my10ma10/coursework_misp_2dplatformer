#pragma once
#include "Entity.h"

class Person : public Entity
{
public:
	Person(Vector2f size, Vector2f position);
	Person(Texture* texture, Vector2f size, Vector2f position);


	const Texture* getTexture() const;
	RectangleShape getBody() const;
	Vector2f getPosition() const;
	Vector2f getSpeed() const;
	Collider getCollider();
	Vector2f getSize() const;

protected:
};

