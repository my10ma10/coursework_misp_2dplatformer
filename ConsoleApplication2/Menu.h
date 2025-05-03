#pragma once
#include "Button.h"
#include "Consts.h"
#include <functional>
#include <vector>
#include <SFML/Graphics.hpp>

enum class GameState {
    Main,
    Game,
    Levels,
    Complete,
    GameOver,
    Paused
};

class Menu
{
public:
    Menu();
    Menu(RenderWindow& window, GameState& state, unsigned int& currLevel);
    void create(RenderWindow* window, GameState* state, unsigned int* currLevel);
    void update(GameState state, unsigned int availableLevel, unsigned int currentLevel);
    void render(GameState state);
    void restartTimer();

    void setCallback(const std::function<void(bool)>& callback);
    void setClickable(bool pred);

    Vector2f getCenter() const;
    unsigned int getLevelNumber() const;

private:
    void initMainMenu(Vector2f buttonSize);
    void initLevelsMenu(Vector2f buttonSize);
    void initCompleteMenu(Vector2f buttonSize);
    void initGameoverMenu(Vector2f buttonSize);
    void initPauseMenu(Vector2f buttonSize);
    void updateMainMenu();
    void updateLevelsMenu();
    void updateCompleteMenu();
    void updateGameoverMenu();
    void updatePauseMenu();
    void updateTransparent(unsigned int availableLevel, unsigned int currentLevel);
    void drawButtons(std::vector<Button> buttons);

    std::function<void(bool)> pauseCallback;

    RenderWindow* window = nullptr;
    GameState* currentState = nullptr;
    unsigned int* levelNumber = nullptr;
    std::vector<Button> mainButtons;
    std::vector<Button> levelsButtons;
    std::vector<Button> completeButtons;
    std::vector<Button> gameoverButtons;
    std::vector<Button> pauseButtons;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Font font;
    Clock clickTimer;
    Time clickDelay = milliseconds(200);
    Color shapeColor = Color(56, 60, 74);
    Color textColor = Color::White;
    Color transparentShapeColor = Color(shapeColor.r, shapeColor.g, shapeColor.b, shapeColor.a * 0.4);
    bool isClickable;
};

