#include "Menu.h"

Menu::Menu(RenderWindow& window): window(window)
{
    if (!this->font.loadFromFile("Fonts\\Rubik-VariableFont_wght.ttf"))
    {
        std::cerr << "Can't load a font";
    }
    Vector2f buttonSize(320, 160);
    initMainMenu(buttonSize);
    initLevelsMenu(buttonSize);
}

void Menu::initMainMenu(Vector2f buttonSize)
{
    mainButtons.emplace_back(Button("Start Game", Color::Blue, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f - buttonSize.y)));
    mainButtons.emplace_back(Button("Exit", Color::Blue, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f + buttonSize.y)));

}

void Menu::initLevelsMenu(Vector2f buttonSize)
{
    float deltaX = WindowWidth / 2.0f + 80;
    levelsButtons.emplace_back(Button("Back", Color::Blue, font, \
        buttonSize, Vector2f(deltaX - buttonSize.y / 2, WindowHeight / 2.0f + 1.5f * buttonSize.y)));

    buttonSize = Vector2f(120, 120);
    levelsButtons.emplace_back(Button("1", Color::Blue, font, \
        buttonSize, Vector2f(deltaX - 2 * buttonSize.x, WindowHeight / 2.0f)));
    levelsButtons.emplace_back(Button("2", Color::Blue, font, \
        buttonSize, Vector2f(deltaX - buttonSize.x, WindowHeight / 2.0f)));
    levelsButtons.emplace_back(Button("3", Color::Blue, font, \
        buttonSize, Vector2f(deltaX, WindowHeight / 2.0f)));
    levelsButtons.emplace_back(Button("4", Color::Blue, font, \
        buttonSize, Vector2f(deltaX + buttonSize.x, WindowHeight / 2.0f)));
    levelsButtons.emplace_back(Button("5", Color::Blue, font, \
        buttonSize, Vector2f(deltaX + 2 * buttonSize.x, WindowHeight / 2.0f)));
}

void Menu::update()
{
    switch (currentState)
    {
    case GameState::Main:
        updateMainMenu();
        break;
    case GameState::Game:
        break;
    case GameState::Levels:
        updateLevelsMenu();
        break;
    case GameState::Achievements:
        break;
    case GameState::Pause:
        break;
    case GameState::Complete:
        break;
    case GameState::GameOver:
        break;
    case GameState::Exit:
        break;
    default:
        break;
    }
    //std::cout << static_cast<int>(currentState) << std::endl;
}

void Menu::updateMainMenu()
{
    if (!mainButtons.empty())
    {
        for (auto& button : mainButtons)
        {
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))));
            if (button.isClicked())
            {
                if (button.getText().getString() == "Start Game")
                {
                    currentState = GameState::Levels;
                }
                else if (button.getText().getString() == "Exit")
                {
                    currentState = GameState::Exit;
                    window.close();
                }
            }
        }
    }
}

void Menu::updateLevelsMenu()
{
    if (!levelsButtons.empty())
    {
        for (auto& button : levelsButtons)
        {
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))));
            if (button.isClicked())
            {// можно перебором строки 12345
                if (button.getText().getString() == "1")
                {
                    currentState = GameState::Game;
                }
                else if (button.getText().getString() == "2")
                {
                    currentState = GameState::Game;
                }
                else if (button.getText().getString() == "Back")
                {
                    currentState = GameState::Main;
                }
            }
        }
    }
}

void Menu::render()
{
    switch (currentState)
    {
    case GameState::Main:
        if (!mainButtons.empty())
        {
            for (auto& button : mainButtons)
            {
                button.draw(window);
            }
        }
        break;
    case GameState::Game:
        break;
    case GameState::Levels:
        if (!levelsButtons.empty())
        {
            for (auto& button : levelsButtons)
            {
                button.draw(window);
            }
        }
        break;
    case GameState::Achievements:
        break;
    case GameState::Pause:
        break;
    case GameState::Complete:
        break;
    case GameState::GameOver:
        break;
    case GameState::Exit:
        break;
    default:
        break;
    }
}

Vector2f Menu::getCenter() const
{
    for (auto& button : mainButtons)
    {
        return Vector2f(button.getPosition().x + 120.0f, window.getSize().y / 2.0f - 80.0f); // магия
    }
}

GameState Menu::getState() const {
	return currentState;
}