//
// Created by Jacopo Uggeri on 20/08/2025.
//

#include "game/Player.h"
#include "game/physics/Vec2.h"

void Player::step(double deltaSeconds) {
    constexpr static float SPEED = 10.0f;
    constexpr static float LERP_SPEED = 5.0f;
    float lerpFactor = 1.0f - std::exp(-LERP_SPEED * deltaSeconds);
    direction = phys::lerp(direction, targetDirection, lerpFactor);
    body_.velocity = direction * SPEED;
    constexpr float GRAVITY = 300;
    body_.acceleration.y = GRAVITY;
    body_.step(deltaSeconds);
}