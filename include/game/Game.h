//
// Created by Jacopo Uggeri on 15/08/2025.
//
#pragma once

#include "game/GameState.h"
#include "graphics/Renderer.h"
#include "input/InputManager.h"

class Game {
public:
    bool init();
    void loop();

private:
    GameState gameState_ {};
    Renderer renderer_ {};
    InputManager inputManager_ {};

    void step(double deltaSeconds);

public:
    Game() = default;
    ~Game() = default;
    // Delete copy operations
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
    // Delete move operations
    Game(Game&&) = delete;
    Game& operator=(Game&&) = delete;
};
