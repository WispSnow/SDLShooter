#include <iostream>
#include "Game.h"

int main(int, char**) {
    Game& game = Game::getInstance();
    game.init();
    game.run();
    
    return 0;
}