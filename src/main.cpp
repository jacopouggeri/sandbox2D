#include "core/CONST.h"
#include "core/GameState.h"
#include "core/ioevents.h"
#include "core/Graphics.h"
#include <SDL2/SDL.h>
#include <iostream>

void quitGracefully(const GameState& gameState, const Graphics& graphics) {
    graphics.destroy();
}

void capFPS(const Uint64 frameStart, const double targetFrameMS) {
    Uint64 frameEnd = SDL_GetPerformanceCounter();

    if (double elapsedMS = static_cast<double>(frameEnd - frameStart) * 1000.0 / static_cast<double>(SDL_GetPerformanceFrequency());
        elapsedMS < targetFrameMS) {
        // sleep most of the time
        SDL_Delay(static_cast<uint32_t>(targetFrameMS - elapsedMS));

        // busy wait remainder
        while (true) {
            frameEnd = SDL_GetPerformanceCounter();
            elapsedMS = static_cast<double>(frameEnd - frameStart) * 1000.0 / static_cast<double>(SDL_GetPerformanceFrequency());
            if (elapsedMS >= targetFrameMS) break;
        }
    }
}


void loop(GameState& gameState, const Graphics& graphics) {
    uint64_t lastStep = SDL_GetPerformanceCounter();
    const uint64_t perfFreq = SDL_GetPerformanceFrequency();
    SDL_Event e;

    while (gameState.running) {
        constexpr double targetFps = 60.0;
        const uint64_t frameStart = SDL_GetPerformanceCounter();
        handleEvents(gameState, &e, graphics.window);

        if (!gameState.paused) {
            const double deltaTime = static_cast<double>(frameStart - lastStep) / static_cast<double>(perfFreq);
            handlePlayerInput(gameState);
            gameState.step(deltaTime);
        }
        lastStep = frameStart;

        draw(graphics, gameState);
        capFPS(frameStart, 1000.0 / targetFps);
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