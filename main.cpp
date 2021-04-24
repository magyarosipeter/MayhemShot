#include <ctime>
#include "Game.h"

int main() {

    std::srand(time(0));

    Game game;
    game.run();

    return 0;
}
