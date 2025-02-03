#include "Game.h"


int main() {
    //Game Loop
    Game game;

    while (game.getIsRunning())
    {
        //Update game loop
        game.update();
        //Render
        game.render();
    }
    return 0;
}