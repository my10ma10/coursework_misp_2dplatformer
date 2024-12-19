#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "Consts.h"

enum class GameState {
    Menu,
    Game,
    Settings,
    Exit
};

class Menu
{
public:
    Menu(RenderWindow& window);

    void update();
    void render();
    GameState getState() const;


private:
    RenderWindow& window;
    std::vector<Button> buttons;
    GameState currentState = GameState::Menu;
    Texture backgroundTexture;
    Sprite backgroundSprite;
    Font font;
};

