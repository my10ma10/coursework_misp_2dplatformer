#pragma once
#include "Entity.h"

enum class ObjectType { Coin, Potion, Armor, Bubble, Boot, Portal };

class Object : public Entity
{
public:
	Object();
	Object(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, ObjectType objectType,
		Vector2f bodySize = Vector2f(16.0f, 16.0f));

	void update(float time);
	void draw(RenderWindow& window) override;
	void setBonusIconSprite(std::string& path);

	ObjectType getType() const;
private:
	Texture bonusIconTexture;
	Sprite bonusIconSprite;
	ObjectType objectType;
};


