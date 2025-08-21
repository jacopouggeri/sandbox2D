//
// Created by Jacopo Uggeri on 20/08/2025.
//
#pragma once
#include "game/Player.h"
#include "physics/PhysicsWorld.h"
#include "world/World.h"

struct GameState {
    uint64_t gameTicks = 0;
    bool running = true;
    bool paused = true;
    bool debugMode = true;
    Player player {};
    World world {};
    phys::PhysicsWorld physicsWorld {};

    bool unpaused() const { return !paused; }
};