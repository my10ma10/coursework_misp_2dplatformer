#include "Game.h"

int main()
{
    GameState gameState = GameState::Main;
    unsigned int levelNumber = 1;
    Game game(gameState, "Image\\icon.png", "Image\\back3.png", levelNumber);
    game.run();  
    return 0;
}

