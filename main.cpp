#include "Game.h"


int main() {
    //
    std::srand(static_cast<unsigned>(NULL));

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