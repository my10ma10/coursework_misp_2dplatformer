#pragma once
#include "Button.h"
#include "Game.h"
#include "Level.h"
#include "View.h"
#include "Menu.h"

class Game
{
public:
    Game(const std::string& iconPath, const std::string& coinSheetPath, const std::string& bonusSheetPath, \
        const std::string& backgroundPath, unsigned int levelIndex);
    void run();

private:
    void processEvents();
    void update(float timeStep);
    void render();

    void updateState();
    void changeViewZoom(View& view);
    void changeViewAspectRatio(const RenderWindow& window, View& view) const;


    RenderWindow window;
    View levelView;
    View menuView;
    Clock clock;

    GameState gameState;
    Menu menu;
    Level level;
    unsigned int levelIndex;

    const float timeStep;
    float accumulator;
    bool isPaused;

    Sprite playerAndViewCollideSprite;
    Collider playerAndViewCollider;
    Sprite levelLimitViewSprite;
    Collider backCollider;
};


