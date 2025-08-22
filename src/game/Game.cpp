//
// Created by Jacopo Uggeri on 15/08/2025.
//

#include "game/Game.h"
#include "game/GameState.h"

#include <chrono>

bool Game::init() {
    if (!renderer_.init(
        config::graphics::WINDOW_SIZE.x,
        config::graphics::WINDOW_SIZE.y,
        config::GAME_NAME)) {
        return false;
    }
    if (!inputManager_.init()) {
        return false;
    }
    gameState_.world.init();
    return true;
}

void Game::step(double deltaSeconds) {
    gameState_.player.move(deltaSeconds);
}

double getSecondsNow() {
    const auto now = std::chrono::steady_clock::now();
    const auto duration = now.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::duration<double>>(duration).count();
}

void Game::loop() {
    double lastTime = getSecondsNow();
    double accumulator = 0.0;

    while (gameState_.running) {
        constexpr double FIXED_TIMESTEP = 1.0 / 60.0; // 60Hz physics
        constexpr double MIN_DELTA_SECONDS = 1.0 / 500.0;
        constexpr double MAX_DELTA_SECONDS = 0.25;

        const double currentTime = getSecondsNow();
        double deltaSeconds = currentTime - lastTime;
        lastTime = currentTime;

        deltaSeconds = std::clamp(deltaSeconds, MIN_DELTA_SECONDS, MAX_DELTA_SECONDS);
        accumulator += deltaSeconds;

        inputManager_.handleEvents(gameState_);

        while (accumulator >= FIXED_TIMESTEP) {
            if (gameState_.unpaused()) {
                step(FIXED_TIMESTEP);  // Always pass fixed timestep to physics
                ++gameState_.gameTicks;
            }
            accumulator -= FIXED_TIMESTEP;
        }

        renderer_.render(gameState_, deltaSeconds);
    }
}