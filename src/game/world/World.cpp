//
// Created by Jacopo Uggeri on 19/08/2025.
//

#include "../../../include/game/world/World.h"
#include <iostream>

Tile& Chunk::getTile(int tileX, int tileY) {
    if (tileX < 0 || tileX >= CHUNK_SIZE || tileY < 0 || tileY >= CHUNK_SIZE) {
        std::cerr << "Invalid tile access: (" << tileX << ", " << tileY << ")" << std::endl;
        throw std::out_of_range("Invalid tile access");
    }
    return tiles[tileY*CHUNK_SIZE + tileX];
}

void World::init() {
    for (int chunkIdx = 0; chunkIdx < CHUNK_COUNT; ++chunkIdx) {
        auto& chunk = chunks[chunkIdx];

        for (int tileIdx = 0; tileIdx < CHUNK_SIZE*CHUNK_SIZE; ++tileIdx) {
            auto& tile = chunk.tiles[tileIdx];

            auto [worldX, worldY] = worldCoords(chunkIdx, tileIdx);
            if (worldY > SEA_LEVEL) {
                tile.sprite.textureName = std::string(WALL_TEX);
            }
        }
    }
}

Chunk& World::getChunk(int chunkX, int chunkY) {
    if (chunkX < 0 || chunkX >= WORLD_WIDTH_CHUNKS || chunkY < 0 || chunkY >= WORLD_HEIGHT_CHUNKS) {
        std::cerr << "Invalid chunk access: (" << chunkX << ", " << chunkY << ")" << std::endl;
        throw std::out_of_range("Invalid chunk access");
    }
    return chunks[chunkY*WORLD_WIDTH_CHUNKS + chunkX];
}

Tile& World::getTileGlobal(int worldX, int worldY) {
    const int chunkX = worldX / CHUNK_SIZE;
    const int chunkY = worldY / CHUNK_SIZE;
    const int tileX  = worldX % CHUNK_SIZE;
    const int tileY  = worldY % CHUNK_SIZE;
    return getChunk(chunkX, chunkY).getTile(tileX, tileY);
}