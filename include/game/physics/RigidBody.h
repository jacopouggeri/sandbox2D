//
// Created by Jacopo Uggeri on 21/08/2025.
//

#pragma once
#include "BoundingBox.h"
#include "Vec2.h"
namespace phys {

enum PhysicsLayer {
        Player = 1,
        Wall = 2
};

struct RigidBody {
    Vec2f position {};
    Vec2f velocity {};
    Vec2f acceleration {};
    BoundingBox boundingBox {};

    void step(double deltaSeconds) {
        const float dt = static_cast<float>(deltaSeconds);
        velocity += acceleration * dt;
        position += velocity * dt;
    }

    void collideWith(RigidBody& other) {
        if (boundingBox.overlaps(other.boundingBox)) {
            const Vec2f overlap = other.boundingBox.position - boundingBox.position;
            const Vec2f correction = overlap;
            position += correction * 0.5f;
            other.position -= correction * 0.5f;
        }
    }
};

}