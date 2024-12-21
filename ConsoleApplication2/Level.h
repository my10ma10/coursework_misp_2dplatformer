#pragma once
#include "Consts.h"
#include "Enemy.h"
#include "Object.h"
#include "Bar.h"
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
	Level();
	Level(const std::string& filePathToCoinTexture, const std::string& filePathToBonusTexture, \
		const std::string& filePathToBackGroundTexture, int numberOfLevel);
	
	void update(float time, const View& levelView);
	void draw(RenderWindow& window);

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
	bool getComplete() const;
	Vector2u getSize() const;
	Vector2f getCenter() const;

	Player& getPlayer();
	Vector2f getPlayerPosition();
	int getPlayerEnergy();
	int getPlayerHealth();
	Collider getPlayerSpriteCollider();

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

	bool ñomplete;
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

