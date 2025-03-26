#include "Menu.h"

Menu::Menu(RenderWindow& window, GameState& state, unsigned int& currLevel):
    window(window), isClickable(true),
    currentState(state), levelNumber(currLevel)
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
    initPauseMenu(buttonSize);
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
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f - buttonSize.y / 2.0f)));
    completeButtons.emplace_back(Button(L"Главное меню", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f + buttonSize.y / 2.0f)));
}

void Menu::initGameoverMenu(Vector2f buttonSize)
{
    gameoverButtons.emplace_back(Button(L"Ещё раз", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f - buttonSize.y / 2.0f)));
    gameoverButtons.emplace_back(Button(L"Главное меню", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f + buttonSize.y / 2.0f)));
}

void Menu::initAchievementsMenu(Vector2f buttonSize)
{
}

void Menu::initPauseMenu(Vector2f buttonSize)
{
    pauseButtons.emplace_back(Button(L"Продолжить", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f - buttonSize.y / 2.0f)));
    pauseButtons.emplace_back(Button(L"Главное меню", textColor, shapeColor, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f + buttonSize.y / 2.0f)));
}

void Menu::update(GameState state, unsigned int availableLevel, unsigned int currentLevel)
{
    if (!isClickable)
    {
        if (clickTimer.getElapsedTime() > clickDelay and !Mouse::isButtonPressed(Mouse::Button::Left))
        {
            isClickable = true;
        }
        else
        {
            return;
        }
    }
    switch (state)
    {
    case GameState::Main:
        updateMainMenu();
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
    case GameState::Paused:
        updatePauseMenu();
        break;
    default:
        break;
    }
    updateTransparent(availableLevel, currentLevel);
}

void Menu::restartTimer()
{
    clickTimer.restart();
}

void Menu::updateMainMenu()
{
    if (!mainButtons.empty())
    {
        for (auto& button : mainButtons)
        {
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))), \
                Mouse::isButtonPressed(Mouse::Button::Left));
            if (isClickable and button.getPressed())
            {
                if (button.getText().getString() == L"Начать игру")
                {
                    currentState = GameState::Levels;
                }
                else if (button.getText().getString() == L"Выход")
                {
                    currentState = GameState::Paused;
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
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))), \
                Mouse::isButtonPressed(Mouse::Button::Left));
            if (isClickable and button.getPressed())
            {
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
                levelNumber = std::stoi(button.getText().getString().toAnsiString());
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
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))), \
                Mouse::isButtonPressed(Mouse::Button::Left));
            if (isClickable and button.getPressed())
            {
                if (button.getText().getString() == L"Далее")
                {
                    currentState = GameState::Game;
                    levelNumber += 1;
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
    if (!gameoverButtons.empty())
    {
        for (auto& button : gameoverButtons)
        {
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))), \
                Mouse::isButtonPressed(Mouse::Button::Left));
            if (isClickable and button.getPressed())
            {
                if (button.getText().getString() == L"Ещё раз")
                {
                    currentState = GameState::Game;
                }
                else if (button.getText().getString() == L"Главное меню")
                {
                    currentState = GameState::Main;
                }
            }
        }
    }
}

void Menu::updateAchievementsMenu()
{
}

void Menu::updatePauseMenu()
{
    if (!pauseButtons.empty())
    {
        for (auto& button : pauseButtons)
        {
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))), \
                Mouse::isButtonPressed(Mouse::Button::Left));
            if (isClickable and button.getPressed())
            {
                if (button.getText().getString() == L"Продолжить")
                {
                    currentState = GameState::Game;
                    pauseCallback(false);
                }
                else if (button.getText().getString() == L"Главное меню")
                {
                    currentState = GameState::Main;
                    pauseCallback(false);
                }
            }
        }
    }
}

void Menu::updateTransparent(unsigned int availableLevel, unsigned int currentLevel)
{
    for (auto& button : levelsButtons)
    {
        unsigned int number = std::stoi(button.getText().getString().toAnsiString()); // номер уровня на этой кнопке
        if (number > availableLevel)
        {
            button.setShapeColor(transparentShapeColor);
            button.setClickable(false);
        }
        else
        {
            button.setShapeColor(shapeColor);
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

void Menu::render(GameState state)
{
    switch (state)
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
        drawButtons(achievementsButtons);
        break;
    case GameState::Complete:
        drawButtons(completeButtons);
        break;
    case GameState::GameOver:
        drawButtons(gameoverButtons);
        break;
    case GameState::Paused:
        drawButtons(pauseButtons);
        break;
    default:
        break;
    }
}

void Menu::setCallback(const std::function<void(bool)>& callback)
{
    this->pauseCallback = callback;
}

void Menu::setClickable(bool pred)
{
    isClickable = pred;
}

Vector2f Menu::getCenter() const
{
    for (auto& button : mainButtons)
    {
        return Vector2f(button.getPosition().x + 120.0f, window.getSize().y / 2.0f - 80.0f); // магия
    }
}

unsigned int Menu::getLevelNumber() const
{
    return levelNumber;
}

