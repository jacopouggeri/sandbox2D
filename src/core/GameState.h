//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once

#include "GameConstants.h"
#include "resources/TextureManager.h"
#include "physics/Vec2.h"
#include "world/World.h"


struct Player {
    constexpr static float SPEED = 10.0f;
    phys::Vec2f pos = {WORLD_WIDTH_CHUNKS * CHUNK_SIZE / 2, WORLD_HEIGHT_CHUNKS * CHUNK_SIZE / 2};
    phys::Vec2f vel;
    Sprite sprite {std::string(PLAYER_TEX)};

    void set_velocity(phys::Vec2f v);
    void move(double deltaTime);
};

struct GameState {
    bool running = true;
    bool paused = true;
    Player player;
    World world;

    void step(double deltaTime);
};

#endif //GAMESTATE_H
