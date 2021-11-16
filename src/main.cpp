
#include "game.h"
#include <cstdio>

int main(int argc, char* argv[])
{
    std::ios::sync_with_stdio(false);
    srand(static_cast<unsigned>(time(nullptr)));

    Game* game = new Game();
    game->run();

    return 0;
}