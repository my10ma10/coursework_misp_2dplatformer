#pragma once
#include "Entity.h"

class Object : public Entity
{
public:
	Object();
	Object(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime, \
		Vector2f bodySize = Vector2f(16.0f, 16.0f));

	void update(float time);
	void draw(RenderWindow& window) override;
	void setBonusIconSprite(std::string& path);
private:
	Texture bonusIconTexture;
	Sprite bonusIconSprite;

};


