//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once

#include "GameState.h"
#include "platform/Graphics.h"

class Game {
public:
    bool init();
    void loop();

private:
    GameState gameState_ {};
    Graphics graphics_ {};

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

#endif //GAMESTATE_H
