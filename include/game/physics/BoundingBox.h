//
// Created by Jacopo Uggeri on 21/08/2025.
//

#pragma once
#include "Vec2.h"

namespace phys {

struct BoundingBox {
    Vec2f position;
    Vec2f halfSize;

    bool overlaps(const BoundingBox& other) const {
        return !(position.x + halfSize.x < other.position.x - other.halfSize.x ||
                position.x - halfSize.x > other.position.x + other.halfSize.x ||
                position.y + halfSize.y < other.position.y - other.halfSize.y ||
                position.y - halfSize.y > other.position.y + other.halfSize.y);
    }
};

}