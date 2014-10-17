#include "Game.h"

int main() {
    Game& game = Game::get();
    
    game.init();
    game.start();
    game.end();

    return 0;
}