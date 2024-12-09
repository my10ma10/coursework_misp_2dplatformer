#include "Game.h"

Game::Game(unsigned int levelIndex) : levelIndex(levelIndex)
{
	level = Level("Image\\coin-Sheet.png", "Image\\potion-Sheet.png", \
		"Image\\back3.png", levelIndex);
}

void Game::updateLevel(float time)
{
	level.update(time);
}

void Game::checkPortal()
{
	level.checkPortal(getPlayerPosition());
}

void Game::update(Collider& backCollider, Sprite& levelLimitViewSprite, View& levelView, \
	Sprite& playerAndViewCollideSprite, Collider& playerColliderForView)
{
	checkPortal();

	//collider
	level.updatePlatfotmsCollide();
	level.updateCoinCollecting();
	level.updateColliders(levelView, level.getSize(), backCollider, levelLimitViewSprite, playerAndViewCollideSprite, playerColliderForView);

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
