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
    Achievements,
    Complete,
    GameOver,
    Paused
};

class Menu
{
public:
    Menu(RenderWindow& window, GameState& state, unsigned int& currLevel);
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
    void initAchievementsMenu(Vector2f buttonSize);
    void initPauseMenu(Vector2f buttonSize);
    void updateMainMenu();
    void updateLevelsMenu();
    void updateCompleteMenu();
    void updateGameoverMenu();
    void updateAchievementsMenu();
    void updatePauseMenu();
    void updateTransparent(unsigned int availableLevel, unsigned int currentLevel);
    void drawButtons(std::vector<Button> buttons);

    std::function<void(bool)> pauseCallback;

    RenderWindow& window;
    std::vector<Button> mainButtons;
    std::vector<Button> levelsButtons;
    std::vector<Button> completeButtons;
    std::vector<Button> gameoverButtons;
    std::vector<Button> achievementsButtons;
    std::vector<Button> pauseButtons;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Font font;
    GameState& currentState;
    Clock clickTimer;
    Time clickDelay = milliseconds(200);
    Color shapeColor = Color(56, 60, 74);
    Color textColor = Color::White;
    Color transparentShapeColor = Color(shapeColor.r, shapeColor.g, shapeColor.b, shapeColor.a * 0.4);
    unsigned int& levelNumber;
    bool isClickable;
};

