#pragma once
#include "Bar.h"
#include "Consts.h"
#include "Enemy.h"
#include "Object.h"
#include "Platform.h"
#include "TileMap.h"
#include <cstdlib>
#include <fstream>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <vector>

enum class LevelState {Failed, Complete, Passing};

class Level
{
public:
	Level();
	Level(const std::string& filePathToCoinTexture, const std::string& filePathToBonusTexture, \
		const std::string& filePathToBackGroundTexture, int numberOfLevel);
	void initLevel(int number);
	void update(float time, const View& levelView);
	void draw(RenderWindow& window);
	void restart();
	void changeLevel(int number);

	void checkPortal(Vector2f playerPosition);
	void checkViewIntersect(View& view, const Vector2u& levelSize);
	void updatePlatfotmsCollide();
	void updateBonuses();
	void updateCoinCollecting();
	void updateEnemies(float time);
	void updateColliders(View& levelView, Collider& backCollider, Sprite& levelLimitViewSprite, \
		Sprite& playerAndViewCollideSprite, Collider& playerColliderForView);

	Sprite getBackGroundSprite() const;
	std::vector<Platform>& getPlatforms();
	std::vector<Enemy>& getEnemies();
	std::vector<Object>& getCoins();
	LevelState getState() const;
	Vector2u getSize() const;
	Vector2f getCenter() const;

	unsigned int getNumber() const;
	bool getPlayerLife() const;
	Vector2f getPlayerPosition();

private:
	void loadTextures(const std::string filePathToCoinTexture, const std::string filePathToBonusTexture, \
		const std::string filePathToBackGroundTexture);
	template <typename T>
	void loadInMap(const std::string& path, std::unordered_map<T, Texture>& textures);
	void initEnemies();
	void initBackground();
	void initBonuses();
	void initTileMap();

	LevelState levelState;
	std::vector<Platform> platforms;
	std::vector<Object> coins;
	std::vector<Object> potions;
	std::vector<Object> bonuses;
	std::vector<Enemy> enemies;
	Object portal;
	Player player;
	Sprite platformSprite;
	Sprite coinSprite;
	Sprite bonusSprite;
	Sprite backGroundSprite;
	Bar healthBar;
	Bar energyBar;

	Collider BackCollider;

	TileMap tileMap;
	std::vector<int> tileLevel;
	Vector2u tileSize;
	Vector2u tilesAmount;
	Vector2u mapSize;

	std::unordered_map<EnemyName, Texture> enemyTextures;
	std::unordered_map<ObjectType, Texture> bonusTextures;
	Texture enemyTexture;
	Texture bonusTexture;
	Texture backgroundTexture;
	Texture playerTexture;

	Vector2u levelSize;
	Vector2f position;
	int numberOfLevel;
};


