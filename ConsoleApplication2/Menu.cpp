#include "Menu.h"

Menu::Menu(RenderWindow& window): window(window)
{
    if (!this->font.loadFromFile("Fonts\\Rubik-VariableFont_wght.ttf"))
    {
        std::cerr << "Can't load a font";
    }
    Vector2f buttonSize(160, 80);
	buttons.emplace_back(Button("Start Game", Color::Blue, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f - 160)));
	buttons.emplace_back(Button("Settings", Color::Blue, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f)));
	buttons.emplace_back(Button("Exit", Color::Blue, font, \
        buttonSize, Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f + 160)));

}

void Menu::update()
{
    if (!buttons.empty())
    {
        for (auto& button : buttons) 
        {
            button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))));
            if (button.isClicked()) 
            {
                if (button.getText().getString() == "Start Game") 
                {
                    currentState = GameState::Game;
                }
                else if (button.getText().getString() == "Settings") 
                {
                    currentState = GameState::Settings;
                }
                else if (button.getText().getString() == "Exit") 
                {
                    /*window.close();*/
                }
            }
        }
    }
}

void Menu::render()
{
    if (!buttons.empty())
    {
        for (auto& button : buttons)
        {
            button.draw(window);
        }
    }
}

GameState Menu::getState() const {
	return currentState;
}