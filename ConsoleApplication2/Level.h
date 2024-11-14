#pragma once
#include "Consts.h"
#include "Platform.h"
#include "Object.h"
#include <vector>

enum class ObjectType { COIN, HEART, BONUS };

class Level
{
public:
	Level(int numberOfLevel);
	Level(const std::string filePathToPlatfomsTexture, const std::string filePathToCoinTexture, \
		const std::string filePathToBonusTexture, const std::string filePathToBackGroundTexture, int numberOfLevel);

	void update(float time);
	void draw(RenderWindow& window);
	void setPlatforms();

	Sprite getBackGroundSprite() const;
	void setIntRectToBackGroundSprite(IntRect);
	std::vector<Platform>& getPlatforms();

private:
	bool isComplete;
	std::vector<Platform> platforms; // size, position
	std::vector<Object> coins;
	std::vector<Object> bonuses;
	Sprite platformSprite;
	Sprite coinSprite;
	Sprite bonusSprite;
	Sprite backGroundSprite;


	Texture platformTexture;
	Texture coinTexture;
	Texture bonusTexture;
	Texture backGroundTexture;


	Vector2f position;
	int numberOfLevel;
};

