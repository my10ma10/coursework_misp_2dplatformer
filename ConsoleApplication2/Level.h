#pragma once
#include "Consts.h"
#include "Enemy.h"
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
	void setCoins();
	void setBonuses();

	Sprite getBackGroundSprite() const;
	std::vector<Platform>& getPlatforms();
	//std::vector<Enemy>& getEnemies();
	Vector2i getSize() const;
	Vector2f getCenter() const;

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

	Vector2i size;
	Vector2f position;
	int numberOfLevel;
};

