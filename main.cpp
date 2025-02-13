#include "Game.h"
#include <iostream>

int main() {
    //Game Loop
    Game game;
    while (game.running() && !game.getEndGame())
    {
        //Update game loop
        game.update();
        //Render
        game.render();
    }
    return 0;
}