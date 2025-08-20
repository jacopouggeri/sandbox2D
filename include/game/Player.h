//
// Created by Jacopo Uggeri on 20/08/2025.
//

#ifndef SANDBOX2D_PLAYER_H
#define SANDBOX2D_PLAYER_H
#include "physics/Vec2.h"
#include "resources/TextureManager.h"
#include "world/World.h"

struct Player {
    constexpr static float SPEED = 10.0f;
    constexpr static float JUMP_SPEED = 10.0f;
    constexpr static phys::Vec2f PLAYER_START_POS {static_cast<phys::Vec2f>(WORLD_SIZE) / 2.0f};
    phys::Vec2f pos = PLAYER_START_POS;
    phys::Vec2f vel;
    Sprite sprite {std::string(PLAYER_TEX)};

    void set_velocity(phys::Vec2f v);
    void move(double deltaSeconds);
};

#endif //SANDBOX2D_PLAYER_H