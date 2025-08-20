//
// Created by Jacopo Uggeri on 15/08/2025.
//

#include "../../include/game/Game.h"
#include "../../include/platform/InputSource.h"

bool Game::init() {
    if (!graphics_.init(WINDOW_SIZE.x, WINDOW_SIZE.y, GAME_NAME)) {
        return false;
    }
    gameState_.world.init();
    return true;
}

void Game::step(double deltaSeconds) {
    gameState_.player.move(deltaSeconds);
}

void Game::loop() {
    uint64_t lastStep = SDL_GetPerformanceCounter();
    const uint64_t perfFreq = SDL_GetPerformanceFrequency();
    int frameCounter = 0;
    SDL_Event e;

    // Temporary hack to make the camera center on the player from the start
    graphics_.cameraSnap(gameState_.player);

    while (gameState_.running) {
        const uint64_t frameStart = SDL_GetPerformanceCounter();
        handleEvents(gameState_, &e);

        const auto elapsedSeconds = static_cast<double>(frameStart - lastStep);
        const double rawDeltaSeconds = elapsedSeconds / static_cast<double>(perfFreq);
        const double deltaSeconds = std::clamp(rawDeltaSeconds, 1.0 / 500.0, 1.0);

        if (!gameState_.paused) {
            handlePlayerInput(gameState_);
            step(deltaSeconds);
            graphics_.cameraFollow(gameState_.player, deltaSeconds);
        }
        lastStep = frameStart;

        const double fps = 1.0 / deltaSeconds;
        if (constexpr int FPS_UPDATE_FRAMES = 10; frameCounter % FPS_UPDATE_FRAMES == 0) graphics_.setFPS(fps);
        graphics_.draw(gameState_);
        frameCounter++;
    }
}