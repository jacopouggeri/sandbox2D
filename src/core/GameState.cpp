//
// Created by Jacopo Uggeri on 15/08/2025.
//

#include "GameState.h"

void Player::set_velocity(const phys::Vec2f v) {
    vel.x = v.x;
    vel.y = v.y;
}

void Player::move(const double deltaTime) {
    pos.x += SPEED * vel.x * static_cast<float>(deltaTime);
    pos.y += SPEED * vel.y * static_cast<float>(deltaTime);
}

phys::Vec2i Player::pos_i() const {
    return {static_cast<int>(pos.x), static_cast<int>(pos.y)};
}

void GameState::step(double deltaTime) {
    player.move(deltaTime);
}
