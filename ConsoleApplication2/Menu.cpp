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
    initAchievementsMenu(buttonSize);
    initCompleteMenu(buttonSize);
    initGameoverMenu(buttonSize);
}

void Menu::initMainMenu(Vector2f buttonSize)
{
    mainButtons.emplace_back(Button(L"Начать игру", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f - buttonSize.y)));
    mainButtons.emplace_back(Button(L"Выход", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f + buttonSize.y)));

}

void Menu::initLevelsMenu(Vector2f buttonSize)
{
    float deltaX = WindowWidth / 2.0f + 80;
    buttonSize = Vector2f(120, 120);
    levelsButtons.emplace_back(Button("1", textColor, shapeColor, font, \
        buttonSize, Vector2f(deltaX - 2 * buttonSize.x, WindowHeight / 2.0f)));
    levelsButtons.emplace_back(Button("2", textColor, shapeColor, font, \
        buttonSize, Vector2f(deltaX - buttonSize.x, WindowHeight / 2.0f)));
    levelsButtons.emplace_back(Button("3", textColor, shapeColor, font, \
        buttonSize, Vector2f(deltaX, WindowHeight / 2.0f)));
    levelsButtons.emplace_back(Button("4", textColor, shapeColor, font, \
        buttonSize, Vector2f(deltaX + buttonSize.x, WindowHeight / 2.0f)));
    levelsButtons.emplace_back(Button("5", textColor, shapeColor, font, \
        buttonSize, Vector2f(deltaX + 2 * buttonSize.x, WindowHeight / 2.0f)));
}

void Menu::initCompleteMenu(Vector2f buttonSize)
{
    completeButtons.emplace_back(Button(L"Далее", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f + buttonSize.y / 2.0f)));
    completeButtons.emplace_back(Button(L"Главное меню", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f - buttonSize.y / 2.0f)));
}

void Menu::initGameoverMenu(Vector2f buttonSize)
{
    gameoverButtons.emplace_back(Button(L"Ещё раз", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f + buttonSize.y / 2.0f)));
    completeButtons.emplace_back(Button(L"Главное меню", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f - buttonSize.y / 2.0f)));
}

void Menu::initAchievementsMenu(Vector2f buttonSize)
{
}

void Menu::update(unsigned int availableLevel, unsigned int currentLevel)
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
        updateAchievementsMenu();
        break;
    case GameState::Complete:
        updateCompleteMenu();
        break;
    case GameState::GameOver:
        updateGameoverMenu();
        break;
    case GameState::Exit:
        break;
    default:
        break;
    }
    updateTransparent(availableLevel, currentLevel);
}

void Menu::updateMainMenu()
{
    if (!mainButtons.empty())
    {
        for (auto& button : mainButtons)
        {
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))));
            if (button.getPressed())
            {
                if (button.getText().getString() == L"Начать игру")
                {
                    currentState = GameState::Levels;
                }
                else if (button.getText().getString() == L"Выход")
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
            if (button.getPressed())
            {// можно перебором строки 12345
                if (button.getText().getString() == "1")
                {
                    currentState = GameState::Game;
                }
                else if (button.getText().getString() == "2")
                {
                    currentState = GameState::Game;
                }
                else if (button.getText().getString() == "3")
                {
                    currentState = GameState::Game;
                }
                else if (button.getText().getString() == "4")
                {
                    currentState = GameState::Game;
                }
                else if (button.getText().getString() == "5")
                {
                    currentState = GameState::Game;
                }
            }
        }
    }
}

void Menu::updateCompleteMenu()
{
    if (!completeButtons.empty())
    {
        for (auto& button : completeButtons)
        {
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))));
            if (button.getPressed())
            {
                if (button.getText().getString() == L"Далее")
                {
                    // next level
                }
                else if (button.getText().getString() == L"Главное меню")
                {
                    currentState = GameState::Main;
                }
            }
        }
    }
}

void Menu::updateGameoverMenu()
{
}

void Menu::updateAchievementsMenu()
{
}

// дебаг
void Menu::updateTransparent(unsigned int availableLevel, unsigned int currentLevel)
{
    for (auto& button : levelsButtons)
    {
        unsigned int number = std::stoi(button.getText().getString().toAnsiString()); //@ номер уровня на этой кнопке
        if (number > availableLevel)
        {
            button.setShapeColor(transparentShapeColor);
            button.setClickable(false);
        }
        else
        {
            button.setClickable(true);
        }
    }
}

void Menu::drawButtons(std::vector<Button> buttons)
{
    if (!buttons.empty())
    {
        for (auto& button : buttons)
        {
            button.draw(window);
        }
    }
}

void Menu::render()
{
    switch (currentState)
    {
    case GameState::Main:
        drawButtons(mainButtons);
        break;
    case GameState::Game:
        break;
    case GameState::Levels:
        drawButtons(levelsButtons);
        break;
    case GameState::Achievements:
        break;
    case GameState::Complete:
        drawButtons(completeButtons);
        break;
    case GameState::GameOver:
        drawButtons(gameoverButtons);
        break;
    case GameState::Exit:
        break;
    default:
        break;
    }
}

void Menu::setState(GameState state)
{
    currentState = state;
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