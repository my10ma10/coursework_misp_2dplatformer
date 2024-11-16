#pragma once
#include "Entity.h"

class Object : public Entity
{
public:
	Object();
	Object(Texture* texture, Vector2f position, Vector2u imageCount, float switchTime);

	void update(float time);
	void draw(RenderWindow& window);
	void setBonusIconSprite(std::string& path);
private:
	Texture bonusIconTexture;
	Sprite bonusIconSprite;

};


