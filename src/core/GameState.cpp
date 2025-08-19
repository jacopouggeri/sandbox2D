//
// Created by Jacopo Uggeri on 15/08/2025.
//

#include "GameState.h"

void Player::set_velocity(phys::Vec2f v) {
    vel.x = v.x;
    vel.y = v.y;
}

void Player::move(double deltaTime) {
    const auto dt = static_cast<float>(deltaTime);
    pos.x += SPEED * vel.x * dt;
    pos.y += SPEED * vel.y * dt;
}

void GameState::step(double deltaTime) {
    player.move(deltaTime);
}
