#include "../game/Config.h"
#include "../game/GameState.h"
#include "ioevents.h"
#include "Graphics.h"
#include <SDL2/SDL.h>
#include <algorithm>

void loop(GameState& gameState, Graphics& graphics) {
    uint64_t lastStep = SDL_GetPerformanceCounter();
    const uint64_t perfFreq = SDL_GetPerformanceFrequency();
    int frameCounter = 0;
    SDL_Event e;

    // Temporary hack to make the camera center on the player from the start
    graphics.cameraSnap(gameState.player);

    while (gameState.running) {
        const uint64_t frameStart = SDL_GetPerformanceCounter();
        handleEvents(gameState, &e);

        const auto elapsedSeconds = static_cast<double>(frameStart - lastStep);
        const double rawDeltaSeconds = elapsedSeconds / static_cast<double>(perfFreq);
        const double deltaSeconds = std::clamp(rawDeltaSeconds, 1.0 / 500.0, 1.0);

        if (!gameState.paused) {
            handlePlayerInput(gameState);
            gameState.step(deltaSeconds);
            graphics.cameraFollow(gameState.player, deltaSeconds);
        }
        lastStep = frameStart;

        const double fps = 1.0 / deltaSeconds;
        if (constexpr int FPS_UPDATE_FRAMES = 10; frameCounter % FPS_UPDATE_FRAMES == 0) graphics.setFPS(fps);
        graphics.draw(gameState);
        frameCounter++;
    }
}

int main() {
    GameState gameState {};
    Graphics graphics {};

    if (!graphics.init(WINDOW_SIZE.x, WINDOW_SIZE.y, GAME_NAME)) {
        return EXIT_FAILURE;
    }

    gameState.world.init();
    loop(gameState, graphics);
    return EXIT_SUCCESS;
}