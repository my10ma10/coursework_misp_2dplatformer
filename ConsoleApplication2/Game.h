#pragma once
#include "Animation.h"
#include "Bar.h"
#include "Button.h"
#include "Game.h"
#include "Level.h"
#include "View.h"

class Game
{
public:
    Game(const std::string& filePathToCoinTexture, const std::string& filePathToBonusTexture, \
        const std::string& filePathToBackGroundTexture, unsigned int levelIndex);

    void updateLevel(float time);
    void checkPortal();
    void update(View& levelView, Collider& backCollider, Sprite& levelLimitViewSprite, \
        Sprite& playerAndViewCollideSprite, Collider& playerColliderForView);

    
    void render(RenderWindow& window);

    bool getLevelComplete() const;
    std::vector<Object>& getLevelCoins();
    std::vector<Enemy>& getLevelEnemies();
    std::vector<Platform>& getLevelPlatforms();

    Vector2u getLevelSize();
    Vector2f getPlayerPosition();
    int getPlayerEnergy();
    int getPlayerHealth();
    Collider getPlayerSpriteCollider();


private:
    Level level;
    unsigned int levelIndex;

};


