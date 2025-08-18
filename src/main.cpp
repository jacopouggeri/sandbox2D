#include "core/CONST.h"
#include "core/GameState.h"
#include "core/ioevents.h"
#include "core/Graphics.h"
#include <SDL2/SDL.h>
#include <iostream>

constexpr int STEP_DELAY_MS = 100; // ms between automatic steps when running

void quitGracefully(const GameState& gameState, const Graphics& graphics) {
    graphics.destroy();
}


void run(GameState& gameState, const Graphics& graphics) {
    uint32_t lastStep = SDL_GetTicks();

    while (gameState.running) {
        SDL_Event e;
        handleEvents(gameState, &e, graphics.window);

        if (const uint32_t now = SDL_GetTicks();
            !gameState.paused &&
            now - lastStep >= STEP_DELAY_MS)
        {
            lastStep = now;
        }

        draw(graphics, gameState);
    }
}

// Must call quitGracefully if init succeeds

int main(int argc, char** args) {
    GameState gameState {};
    Graphics graphics;

    if (graphics.init(1280, 720, GAME_NAME.c_str()) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }

    run(gameState, graphics);

    quitGracefully(gameState, graphics);
    return EXIT_SUCCESS;
}