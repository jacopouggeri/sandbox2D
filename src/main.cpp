#include "core/GameConstants.h"
#include "core/GameState.h"
#include "core/ioevents.h"
#include "core/Graphics.h"
#include <SDL2/SDL.h>

void loop(GameState& gameState, Graphics& graphics) {
    uint64_t lastStep = SDL_GetPerformanceCounter();
    const uint64_t perfFreq = SDL_GetPerformanceFrequency();
    SDL_Event e;

    while (gameState.running) {
        const uint64_t frameStart = SDL_GetPerformanceCounter();
        handleEvents(gameState, &e);

        const double deltaTime = static_cast<double>(frameStart - lastStep) / static_cast<double>(perfFreq);
        if (!gameState.paused) {
            handlePlayerInput(gameState);
            gameState.step(deltaTime);
            graphics.cameraFollow(gameState.player);
        }
        lastStep = frameStart;

        const double fps = 1.0 / deltaTime;
        if (lastStep % 5 == 0) graphics.setFPS(fps);
        graphics.draw(gameState);
    }
}

int main() {
    GameState gameState {};
    Graphics graphics;

    if (!graphics.init(WINDOW_SIZE.x, WINDOW_SIZE.y, GAME_NAME)) {
        return EXIT_FAILURE;
    }

    gameState.world.init();
    loop(gameState, graphics);
    return EXIT_SUCCESS;
}