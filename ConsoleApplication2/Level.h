#pragma once
#include "Consts.h"
#include "Enemy.h"
#include "Object.h"
#include "Platform.h"
#include "TileMap.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <queue>

enum class ObjectType { COIN, HEART, BONUS };

class Level
{
public:
	Level(const std::string filePathToCoinTexture, const std::string filePathToBonusTexture, \
		const std::string filePathToBackGroundTexture, Player* player = nullptr, int numberOfLevel = 5);
	
	void update(float time);
	void draw(RenderWindow& window);
	void loadTextures(const std::string filePathToCoinTexture, const std::string filePathToBonusTexture, \
		const std::string filePathToBackGroundTexture);
	void loadEnemyTextures();
	void setEnemies(Player* playerPtr);
	void setBackground();
	void setBonuses();
	void setCoins();
	void setTileMap();

	Sprite getBackGroundSprite() const;
	std::vector<Platform>& getPlatforms();
	std::vector<Enemy>& getEnemies();
	Vector2u getSize() const;
	Vector2f getCenter() const;

private:
	bool isComplete;
	std::vector<Platform> platforms; // size, position
	std::vector<Object> coins;
	std::vector<Object> bonuses;
	std::vector<Enemy> enemies;
	Object portal;
	Sprite platformSprite;
	Sprite coinSprite;
	Sprite bonusSprite;
	Sprite backGroundSprite;

	TileMap tileMap;
	std::vector<int> tileLevel;
	Vector2u tileSize;
	Vector2u tilesAmount;
	Vector2u mapSize;

	std::unordered_map<EnemyName, Texture> enemyTextures;
	Texture enemyTexture;
	Texture coinTexture;
	Texture bonusTexture;
	Texture backgroundTexture;
	Texture portalTexture;

	Vector2u levelSize;
	Vector2f position;
	int numberOfLevel;
};

