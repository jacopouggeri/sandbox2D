//
// Created by Jacopo Uggeri on 19/08/2025.
//

#include "../../../include/game/world/World.h"
#include <iostream>

Tile& Chunk::getTile(int tileX, int tileY) {
    if (tileX < 0 || tileX >= world::CHUNK_SIZE || tileY < 0 || tileY >= world::CHUNK_SIZE) {
        std::cerr << "Invalid tile access: (" << tileX << ", " << tileY << ")" << std::endl;
        throw std::out_of_range("Invalid tile access");
    }
    return tiles[tileY* world::CHUNK_SIZE + tileX];
}

void World::init() {
    for (int chunkIdx = 0; chunkIdx < world::CHUNK_COUNT; ++chunkIdx) {
        auto& chunk = chunks[chunkIdx];

        for (int tileIdx = 0; tileIdx < world::CHUNK_SIZE* world::CHUNK_SIZE; ++tileIdx) {
            auto& tile = chunk.tiles[tileIdx];

            auto [worldX, worldY] = worldCoords(chunkIdx, tileIdx);
            if (worldY > world::SEA_LEVEL) {
                tile.sprite.textureName = std::string(config::resources::WALL_TEX);
            }
        }
    }
}

Chunk& World::getChunk(int chunkX, int chunkY) {
    if (chunkX < 0 || chunkX >= world::WORLD_WIDTH_CHUNKS || chunkY < 0 || chunkY >= world::WORLD_HEIGHT_CHUNKS) {
        std::cerr << "Invalid chunk access: (" << chunkX << ", " << chunkY << ")" << std::endl;
        throw std::out_of_range("Invalid chunk access");
    }
    return chunks[chunkY* world::WORLD_WIDTH_CHUNKS + chunkX];
}

Tile& World::getTileGlobal(int worldX, int worldY) {
    const int chunkX = worldX / world::CHUNK_SIZE;
    const int chunkY = worldY / world::CHUNK_SIZE;
    const int tileX  = worldX % world::CHUNK_SIZE;
    const int tileY  = worldY % world::CHUNK_SIZE;
    return getChunk(chunkX, chunkY).getTile(tileX, tileY);
}