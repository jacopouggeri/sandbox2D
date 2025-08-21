//
// Created by Jacopo Uggeri on 21/08/2025.
//

#pragma once
#include "DynamicBody.h"
#include "game/world/World.h"
#include <vector>

namespace phys {
class PhysicsWorld {
    std::vector<std::reference_wrapper<DynamicBody>> dynamicBodies {};

public:
    void addBody(DynamicBody& body) {
        dynamicBodies.emplace_back(body);
    }

    void resolveCollisions(double deltaSeconds, World& world) {
        for (auto& bodyRef : dynamicBodies) {
            auto& body = bodyRef.get();
            const Vec2i tilePos = Vec2i(std::floor(body.position.x), std::floor(body.position.y));

            // Check 3x3 grid around the body
            for (int y = -1; y <= 1; ++y) {
                for (int x = -1; x <= 1; ++x) {
                    const int tx = tilePos.x + x;
                    const int ty = tilePos.y + y;

                    if (tx < -world::WORLD_SIZE.x/2 || tx >= world::WORLD_SIZE.x/2 ||
                        ty < -world::WORLD_SIZE.y/2 || ty >= world::WORLD_SIZE.y/2) {
                        continue;
                        }

                    const auto& tile = world.getTileGlobal(tx, ty);
                    if (tile.sprite.textureName.empty()) continue;

                    // Create AABB for the tile (position is tile's center)
                    BoundingBox tileAABB;
                    tileAABB.halfSize = Vec2f(0.5f, 0.5f);  // Half of tile size (1x1)
                    tileAABB.position = Vec2f(tx, ty);  // Center of tile

                    body.collideWith(tileAABB);
                }
            }
        }
    }
};
}