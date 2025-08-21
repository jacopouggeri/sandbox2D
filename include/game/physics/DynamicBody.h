//
// Created by Jacopo Uggeri on 21/08/2025.
//

#pragma once
#include "BoundingBox.h"
#include "Vec2.h"

#include <algorithm>

namespace phys {

struct DynamicBody {
    BoundingBox boundingBox {};
    Vec2f& position {boundingBox.position};
    Vec2f velocity {};
    Vec2f acceleration {};

    void step(double deltaSeconds) {
        const float dt = static_cast<float>(deltaSeconds);
        velocity += acceleration * dt;
        position +=  velocity * dt;
    }

    void collideWith(const BoundingBox& otherBox) {
        if (!boundingBox.overlaps(otherBox)) return;

        // Calculate overlap on both axes
        const float xOverlap = std::min(
            boundingBox.position.x + boundingBox.halfSize.x - (otherBox.position.x - otherBox.halfSize.x),
            otherBox.position.x + otherBox.halfSize.x - (boundingBox.position.x - boundingBox.halfSize.x)
        );

        const float yOverlap = std::min(
            boundingBox.position.y + boundingBox.halfSize.y - (otherBox.position.y - otherBox.halfSize.y),
            otherBox.position.y + otherBox.halfSize.y - (boundingBox.position.y - boundingBox.halfSize.y)
        );

        constexpr float EPSILON = 0.001f;

        if (xOverlap > 0 && xOverlap < yOverlap) {
            float direction = boundingBox.position.x < otherBox.position.x ? -1.0f : 1.0f;
            position.x += (xOverlap + EPSILON) * direction;
            velocity.x = 0;   // stop only along collision axis
        }
        else if (yOverlap > 0) {
            float direction = boundingBox.position.y < otherBox.position.y ? -1.0f : 1.0f;
            position.y += (yOverlap + EPSILON) * direction;
            velocity.y = 0;
        }
    }
};

}