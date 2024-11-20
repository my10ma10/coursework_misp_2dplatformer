#pragma once
#include "Consts.h"
#include "Enemy.h"
#include "Platform.h"
#include "Object.h"
#include "TileMap.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>

enum class ObjectType { COIN, HEART, BONUS };

class Level
{
public:
	Level(const std::string filePathToCoinTexture, \
		const std::string filePathToBonusTexture, const std::string filePathToBackGroundTexture, int numberOfLevel);

	void update(float time);
	void draw(RenderWindow& window);
	std::vector<int> setTileLevel();
	//void setPlatforms();
	void setCoins();
	void setBonuses();

	Sprite getBackGroundSprite() const;
	std::vector<Platform>& getPlatforms();
	//std::vector<Enemy>& getEnemies();
	Vector2u getSize() const;
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

	TileMap map;
	std::vector<int> tileLevel;
	Vector2u tileSize;
	Vector2u tilesAmount;
	Vector2u mapSize;


	Texture coinTexture;
	Texture bonusTexture;
	Texture backGroundTexture;

	Vector2u levelSize;
	Vector2f position;
	int numberOfLevel;
};

