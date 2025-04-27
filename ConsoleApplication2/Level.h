#pragma once
#include "Bar.h"
#include "Consts.h"
#include "Enemy.h"
#include "Object.h"
#include "Platform.h"
#include "TileMap.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>

enum class LevelState {Failed, Complete, Passing};

class Level
{
public:
	Level();
	Level(const std::string& backGroundTexturePath, int numberOfLevel);
	void initLevel(int number);
	void update(float time, const View& levelView);
	void draw(RenderWindow& window);
	void restart();
	void changeLevel(int number);

	void checkPortal(Vector2f playerPosition);
	void checkViewIntersect(View& view, const Vector2u& levelSize);
	void updatePlatfotmsCollide();
	void updateBonuses(float time);
	void updateEnemies(float time);
	void updateColliders(View& levelView, Collider& backCollider, Sprite& levelLimitViewSprite, \
		Sprite& playerAndViewCollideSprite, Collider& playerColliderForView);

	Sprite getBackGroundSprite() const;
	std::vector<Platform>& getPlatforms(unsigned int number);
	std::vector<Enemy>& getEnemies(unsigned int number);
	LevelState getState() const;
	Vector2u getSize() const;
	Vector2f getCenter() const;

	unsigned int getNumber() const;
	bool getPlayerLife() const;
	Vector2f getPlayerPosition();

private:
	template<typename T>
	T stringToType(const std::string& name);

	template<>
	ObjectType stringToType<ObjectType>(const std::string& name);
	template<>
	EnemyName stringToType<EnemyName>(const std::string& name);

	void loadTextures(const std::string backGroundTexturePath);
	template <typename T>
	void loadInMap(const std::string& path, std::unordered_map<T, Texture>& textures);
	void initEnemies();
	void initBackground();
	void initBonuses();
	void initTileMap();
	void initPositions(std::string filePath, 
		std::map<unsigned int, std::map<ObjectType, std::vector<Vector2i>>>& positionsMap);
	void initPositions(std::string filePath,
		std::map<unsigned int, std::map<EnemyName, std::vector<Vector2i>>>& positionsMap);

	LevelState levelState;
	std::vector<std::vector<Platform> > platforms;
	std::vector<std::vector<Object> > bonuses;
	std::vector<std::vector<Enemy> > enemies;
	Object portal;
	Player player;
	Sprite backGroundSprite;
	Bar healthBar;
	Bar energyBar;
	std::map <unsigned int, std::map <ObjectType, std::vector <Vector2i> > > allLevelsObjectsPositions;
	std::map <unsigned int, std::map <EnemyName, std::vector <Vector2i> > > allLevelsEnemiesPositions;

	Collider BackCollider;

	TileMap tileMap;
	std::vector<std::vector<int> > tileLevel;
	Vector2u tileSize;
	Vector2u tilesAmount;
	Vector2u mapSize;
	Vector2u portalPosition;
	Vector2u playerPosition;

	std::map <EnemyName, Vector2i> enemiesSize;

	std::unordered_map<EnemyName, Texture> enemyTextures;
	std::unordered_map<ObjectType, Texture> bonusTextures;
	Texture backgroundTexture;
	Texture playerTexture;

	Vector2u levelSize;
	int levelNumber;
	size_t levelIndex;

};


