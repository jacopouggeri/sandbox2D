//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once

#include "GameConstants.h"
#include "resources/TextureManager.h"
#include "physics/Vec2.h"
#include <vector>

struct Tile {
    Sprite sprite;
    phys::Vec2i pos;
};

struct Player {
    constexpr static float SPEED = 200;
    phys::Vec2f pos = {WINDOW_SIZE.x / 2.0f, WINDOW_SIZE.y / 2.0f};
    phys::Vec2f vel;
    Sprite sprite {std::string(PLAYER_TEX)};

    void set_velocity(phys::Vec2f v);
    void move(double deltaTime);
    [[nodiscard]] phys::Vec2i pos_i() const;
};

struct GameState {
    bool running = true;
    bool paused = true;
    Player player;
    std::vector<Tile> tiles {};

    void step(double deltaTime);
};

#endif //GAMESTATE_H
