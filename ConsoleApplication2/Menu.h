#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "Consts.h"

enum class GameState {
    Main,
    Game,
    Levels,
    Achievements,
    Pause,
    Complete,
    GameOver,
    Exit
};

class Menu
{
public:
    Menu(RenderWindow& window);
    void initMainMenu(Vector2f buttonSize);
    void initLevelsMenu(Vector2f buttonSize);
    void update();
    void updateMainMenu();
    void updateLevelsMenu();
    void render();
    Vector2f getCenter() const;
    GameState getState() const;


private:
    RenderWindow& window;
    std::vector<Button> mainButtons;
    std::vector<Button> levelsButtons;
    GameState currentState = GameState::Main;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Font font;
};

