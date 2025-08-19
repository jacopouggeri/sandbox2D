//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once

#include "Sprite.h"
#include "physics/Vec2.h"
#include <vector>

#include "GameConstants.h"

struct Tile {
    Sprite sprite;
    phys::Vec2i pos;
};

struct Player {
    constexpr static float SPEED = 200;
    phys::Vec2f pos;
    phys::Vec2f vel;
    Sprite sprite {PLAYER_TEX};

    void set_velocity(const phys::Vec2f v) {
        vel.x = v.x;
        vel.y = v.y;
    }

    void move(const double deltaTime) {
        pos.x += SPEED * vel.x * static_cast<float>(deltaTime);
        pos.y += SPEED * vel.y * static_cast<float>(deltaTime);
    }

    [[nodiscard]] phys::Vec2i pos_i() const {
        return {static_cast<int>(pos.x), static_cast<int>(pos.y)};
    }
};

struct GameState {
    bool running = true;
    bool paused = true;
    Player player;
    std::vector<Tile> tiles {};

    void step(const double deltaTime) {
        player.move(deltaTime);
    }
};

#endif //GAMESTATE_H
