//
// Created by Jacopo Uggeri on 15/08/2025.
//

#include "GameState.h"

void Player::set_velocity(phys::Vec2f v) {
    vel = v;
}

void Player::move(double deltaSeconds) {
    const auto dt = static_cast<float>(deltaSeconds);
    pos +=  vel * SPEED * dt;
}

void GameState::step(double deltaSeconds) {
    player.move(deltaSeconds);
}
