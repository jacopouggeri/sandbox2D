//
// Created by Jacopo Uggeri on 20/08/2025.
//
#pragma once
#include "Player.h"
#include "world/World.h"

struct GameState {
    uint64_t gameTicks = 0;
    bool running = true;
    bool paused = true;
    bool debugMode = true;
    Player player {};
    World world {};

    bool unpaused() const { return !paused; }
};