#include "../../include/game/Game.h"
#include <SDL.h>

int main() {
    Game game {};
    if (!game.init()) return EXIT_FAILURE;
    game.loop();
    return EXIT_SUCCESS;
}