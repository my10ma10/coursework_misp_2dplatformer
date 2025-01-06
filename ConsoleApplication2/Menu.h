#pragma once
#include "Button.h"
#include "Consts.h"
#include <SFML/Graphics.hpp>
#include <vector>

enum class GameState {
    Main,
    Game,
    Levels,
    Achievements,
    Complete,
    GameOver,
    Exit
};

class Menu
{
public:
    Menu(RenderWindow& window);
    void update(unsigned int availableLevel, unsigned int currentLevel);
    void render();

    unsigned int setNextLevel(unsigned int currentLevel);
    void setState(GameState state);

    Vector2f getCenter() const;
    unsigned int getLevelNumber() const;
    GameState getState() const;

private:
    void initMainMenu(Vector2f buttonSize);
    void initLevelsMenu(Vector2f buttonSize);
    void initCompleteMenu(Vector2f buttonSize);
    void initGameoverMenu(Vector2f buttonSize);
    void initAchievementsMenu(Vector2f buttonSize);
    void updateMainMenu();
    void updateLevelsMenu();
    void updateCompleteMenu();
    void updateGameoverMenu();
    void updateAchievementsMenu();
    void updateTransparent(unsigned int availableLevel, unsigned int currentLevel);
    void drawButtons(std::vector<Button> buttons);
    void checkState();

    RenderWindow& window;
    std::vector<Button> mainButtons;
    std::vector<Button> levelsButtons;
    std::vector<Button> completeButtons;
    std::vector<Button> gameoverButtons;
    std::vector<Button> achievementsButtons;
    GameState prevState;
    GameState currentState;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Font font;

    Clock clickTimer;
    Time clickDelay = milliseconds(200);
    bool isClickable;
    Color shapeColor = Color(56, 60, 74);
    Color textColor = Color::White;
    Color transparentShapeColor = Color(shapeColor.r, shapeColor.g, shapeColor.b, shapeColor.a * 0.4);
    unsigned int levelNumber;
};

