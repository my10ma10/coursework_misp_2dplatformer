#pragma once
#include "Button.h"
#include "Game.h"
#include "Level.h"
#include "Menu.h"

class Game
{
public:
    Game(GameState& gameState, const std::string& iconPath, const std::string& backgroundPath, unsigned int& levelIndex);
    void run();

    unsigned int getCurrentLevel() const;

private:
    void processEvents();
    void update(float timeStep);
    void render();
    void updateAvailables();
    void initView();
    void changeViewAspectRatio(View& view) const;
    void checkState();

    RenderWindow window;
    View levelView;
    View menuView;
    Clock clock;

    GameState prevState;
    GameState& currentState;
    Menu menu;
    Level level;
    unsigned int& currentLevel;
    unsigned int availableLevel;

    const float timeStep;
    float accumulator;
    bool isProcessPaused;

    Sprite playerAndViewCollideSprite;
    Collider playerAndViewCollider;
    Sprite levelLimitViewSprite;
    Collider backCollider;
};


