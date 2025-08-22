//
// Created by Jacopo Uggeri on 20/08/2025.
//

#include "game/Player.h"
#include "game/physics/Vec2.h"

void Player::set_velocity(phys::Vec2f v) {
    vel = v;
}

void Player::move(double deltaSeconds) {
    const auto dt = static_cast<float>(deltaSeconds);
    pos +=  vel * SPEED * dt;
}