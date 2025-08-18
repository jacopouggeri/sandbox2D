#include "core/CONST.h"
#include "core/GameState.h"
#include "core/ioevents.h"
#include "core/Graphics.h"
#include <SDL2/SDL.h>
#include <iostream>

void quitGracefully(const GameState& gameState, const Graphics& graphics) {
    graphics.destroy();
}



void loop(GameState& gameState, const Graphics& graphics) {
    constexpr double targetFps = 60.0;
    uint64_t lastStep = SDL_GetPerformanceCounter();
    const uint64_t perfFreq = SDL_GetPerformanceFrequency();

    while (gameState.running) {
        SDL_Event e;
        handleEvents(gameState, &e, graphics.window);

        if (!gameState.paused) {
            const uint64_t now = SDL_GetPerformanceCounter();
            const double deltaTime = static_cast<double>(now - lastStep) / static_cast<double>(perfFreq);
            gameState.step(deltaTime);
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

    loop(gameState, graphics);

    quitGracefully(gameState, graphics);
    return EXIT_SUCCESS;
}