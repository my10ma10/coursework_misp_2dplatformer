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

enum class ObjectType { COIN, HEART, BONUS };
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
	void updateCoinCollecting();
	void updateEnemies();
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
	void loadEnemyTextures();
	void initEnemies();
	void initBackground();
	void initBonuses();
	void initCoins();
	void initPlayer();
	void initTileMap();

	LevelState levelState;
	std::vector<Platform> platforms; // size, position
	std::vector<Object> coins;
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
	Texture enemyTexture;
	Texture coinTexture;
	Texture bonusTexture;
	Texture backgroundTexture;
	Texture portalTexture;
	Texture playerTexture;

	Vector2u levelSize;
	Vector2f position;
	int numberOfLevel;
};

