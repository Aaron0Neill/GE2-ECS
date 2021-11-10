
#include "game.h"

int main(int argc, char* argv[])
{

    std::ios::sync_with_stdio(false);

    Game* game = new Game();
    game->run();

    return 0;
}