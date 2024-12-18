#include "Game.h"

Game::Game(const std::string& filePathToCoinTexture, const std::string& filePathToBonusTexture, \
	const std::string& filePathToBackGroundTexture, unsigned int levelIndex) : levelIndex(levelIndex)
{
	level = Level(filePathToCoinTexture, filePathToBonusTexture, \
		filePathToBackGroundTexture, levelIndex);
}

void Game::updateLevel(float time)
{
	level.update(time);
}

void Game::checkPortal()
{
	level.checkPortal(getPlayerPosition());
}

void Game::update(View& levelView, Collider& backCollider, Sprite& levelLimitViewSprite,  \
	Sprite& playerAndViewCollideSprite, Collider& playerColliderForView)
{
	checkPortal();
	level.updatePlatfotmsCollide();
	level.updateCoinCollecting();
	level.updateColliders(levelView, backCollider, levelLimitViewSprite, \
		playerAndViewCollideSprite, playerColliderForView);

}

void Game::render(RenderWindow& window)
{
	level.draw(window);
}

bool Game::getLevelComplete() const
{
	return level.getComplete();
}

std::vector<Object>& Game::getLevelCoins()
{
	return level.getCoins();
}

std::vector<Enemy>& Game::getLevelEnemies()
{
	return level.getEnemies();
}

std::vector<Platform>& Game::getLevelPlatforms()
{
	return level.getPlatforms();
}

Vector2u Game::getLevelSize()
{
	return level.getSize();
}

Vector2f Game::getPlayerPosition()
{
	return level.getPlayerPosition();
}

int Game::getPlayerEnergy()
{
	return level.getPlayerEnergy();
}

int Game::getPlayerHealth()
{
	return level.getPlayerHealth();
}

Collider Game::getPlayerSpriteCollider()
{
	return level.getPlayerSpriteCollider();
}
