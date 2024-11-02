#pragma once
#include "Entity.h"

class Person : public Entity
{
public:
	Person(Vector2f size, Vector2f position);
	Person(Texture* texture, Vector2f size, Vector2f position);
	//Person(Image& image, Vector2f size, Vector2f position);

	void updateAnimation(int row, float time);

	const Texture* getTexture() const;
	RectangleShape getBody() const;
	Vector2f getPosition() const;
	Vector2f getSpeed() const;
	Collider getCollider();
	Vector2f getSize() const;

protected:
	bool attackType; // 0 - ближний, 1 - дальний
	int health;
	int energy;
};

