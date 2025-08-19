#include "core/GameConstants.h"
#include "core/GameState.h"
#include "core/ioevents.h"
#include "core/Graphics.h"
#include <SDL2/SDL.h>

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


void loop(GameState& gameState, Graphics& graphics) {
    uint64_t lastStep = SDL_GetPerformanceCounter();
    const uint64_t perfFreq = SDL_GetPerformanceFrequency();
    SDL_Event e;

    while (gameState.running) {
        constexpr double targetFps = 60.0;
        const uint64_t frameStart = SDL_GetPerformanceCounter();
        handleEvents(gameState, &e);

        if (!gameState.paused) {
            const double deltaTime = static_cast<double>(frameStart - lastStep) / static_cast<double>(perfFreq);
            handlePlayerInput(gameState);
            gameState.step(deltaTime);
        }
        lastStep = frameStart;

        graphics.draw(gameState);
        capFPS(frameStart, 1000.0 / targetFps);
    }
}

int main() {
    GameState gameState {};
    Graphics graphics;

    if (graphics.init(WINDOW_SIZE.x, WINDOW_SIZE.y, GAME_NAME) != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    gameState.tiles.push_back({{std::string(WALL_TEX)}, {100, 100}});

    loop(gameState, graphics);

    return EXIT_SUCCESS;
}