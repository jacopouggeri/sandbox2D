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
    constexpr static float JUMP_SPEED = 10.0f;
    constexpr static phys::Vec2i WORLD_SIZE {WORLD_WIDTH_CHUNKS * CHUNK_SIZE, WORLD_HEIGHT_CHUNKS * CHUNK_SIZE};
    constexpr static phys::Vec2f PLAYER_START_POS = static_cast<phys::Vec2f>(WORLD_SIZE / 2) ;
    phys::Vec2f pos = PLAYER_START_POS;
    phys::Vec2f vel;
    Sprite sprite {std::string(PLAYER_TEX)};

    void set_velocity(phys::Vec2f v);
    void move(double deltaSeconds);
};

struct GameState {
    bool running = true;
    bool paused = true;
    Player player;
    World world;

    void step(double deltaSeconds);
};

#endif //GAMESTATE_H
