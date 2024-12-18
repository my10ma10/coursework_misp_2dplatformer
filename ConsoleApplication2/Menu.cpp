#include "Menu.h"

Menu::Menu(RenderWindow& window): window(window)
{
	buttons.emplace_back(Button("Start Game", Color::Blue, Vector2f(80, 40), \
		Vector2f(WindowWidth / 2.0f, WindowHeight / 2.0f)));
	buttons.emplace_back(Button("Settings", Color::Blue, Vector2f(80, 40), Vector2f(200, 200)));
	buttons.emplace_back(Button("Exit", Color::Blue, Vector2f(80, 40), Vector2f(200, 300)));
}

void Menu::update()
{
    for (auto& button : buttons) {
        button.update(Vector2i(window.mapPixelToCoords(Mouse::getPosition(window))));
        if (button.isClicked()) {
            if (button.getText().getString() == "Start Game") {
                currentState = GameState::Game;
            }
            else if (button.getText().getString() == "Settings") {
                currentState = GameState::Settings;
            }
            else if (button.getText().getString() == "Exit") {
                window.close();
            }
        }
    }
}

void Menu::render()
{
	for (Button& button : buttons)
	{
		button.draw(window);
	}
    std::cout << "rendering\n";
}

GameState Menu::getState() const {
	return currentState;
}