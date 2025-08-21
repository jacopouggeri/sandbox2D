//
// Created by Jacopo Uggeri on 20/08/2025.
//
#pragma once
#include "physics/Vec2.h"
#include "world/World.h"

class Player {
    constexpr static float SPEED = 10.0f;
    phys::Vec2f pos {};
    phys::Vec2f vel {};
    Sprite sprite {std::string(config::resources::PLAYER_TEX)};

    void setVelocity(phys::Vec2f v);
    void move(double deltaSeconds);
};