//
// Created by Jacopo Uggeri on 19/08/2025.
//
#pragma once

#include "game/Config.h"
#include "game/resources/Sprite.h"
#include <array>

namespace world {
constexpr int CHUNK_SIZE = 16;
constexpr int WORLD_WIDTH_CHUNKS = 8;
constexpr int WORLD_HEIGHT_CHUNKS = 4;
constexpr phys::Vec2i WORLD_SIZE {WORLD_WIDTH_CHUNKS * CHUNK_SIZE, WORLD_HEIGHT_CHUNKS * CHUNK_SIZE};
constexpr int SEA_LEVEL = 0;
constexpr int CHUNK_COUNT = WORLD_WIDTH_CHUNKS * WORLD_HEIGHT_CHUNKS;

}


struct Tile {
    Sprite sprite;
};

struct Chunk {
    std::array<Tile, world::CHUNK_SIZE* world::CHUNK_SIZE> tiles;

    Tile& getTile(int tileX, int tileY);
};

struct World {
    std::array<Chunk, world::CHUNK_COUNT> chunks;

    void init();

    Tile& getTileGlobal(int worldX, int worldY);

    Chunk& getChunk(int chunkX, int chunkY);

    [[nodiscard]] static constexpr phys::Vec2i chunkCoords(int chunkIdx) noexcept {
        return { chunkIdx % world::WORLD_WIDTH_CHUNKS, chunkIdx / world::WORLD_WIDTH_CHUNKS };
    }

    [[nodiscard]] static constexpr phys::Vec2i tileCoords(int tileIdx) noexcept {
        return { tileIdx % world::CHUNK_SIZE, tileIdx / world::CHUNK_SIZE };
    }

    [[nodiscard]] static constexpr phys::Vec2i worldCoords(int chunkIdx, int tileIdx) noexcept {
        const phys::Vec2i chunkPos = chunkCoords(chunkIdx);
        const phys::Vec2i tilePos = tileCoords(tileIdx);
        return chunkPos * world::CHUNK_SIZE + tilePos - world::WORLD_SIZE / 2; // Center the world
    }
};