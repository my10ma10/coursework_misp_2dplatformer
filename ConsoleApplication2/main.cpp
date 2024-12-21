#include "Game.h"

int main()
{
   Game game("Image\\icon.png", "Image\\coin-Sheet.png",
        "Image\\potion-Sheet.png", "Image\\back3.png", 1);
    game.run();  
    return 0;
}

