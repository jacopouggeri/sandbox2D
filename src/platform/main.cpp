#include "game/Game.h"

int main() {
    Game game {};
    if (!game.init()) return EXIT_FAILURE;
    game.loop();
    SDL_Quit();
    return EXIT_SUCCESS;
}