#pragma once
#include "Animation.h"
class Object
{
private:
	Animation animation;
	Texture texture;
	Sprite sprite;
public:
	Object();
	Object(Texture* texture);
	void draw(RenderWindow& window);
	
	void setAnimation(Vector2u imageCount, float switchTime);
	void setTextureRect(const IntRect& rectangle);

	void updateAnimation(int row, float time);
	Sprite getSprite() const;
};


//Object createObject(std::string path) {
//	Texture texture = Texture();
//	Object object;
//	if (texture.loadFromFile("Image\\coin-Sheet.png")) {
//		object = Object(&texture);
//	}
//	return object;
//}