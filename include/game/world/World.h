//
// Created by Jacopo Uggeri on 19/08/2025.
//

#ifndef SANDBOX2D_WORLD_H
#define SANDBOX2D_WORLD_H
#pragma once

#include "../Config.h"
#include "../resources/TextureManager.h"
#include <array>

constexpr int TILE_SIZE = 16 * DRAW_SCALE;
constexpr int CHUNK_SIZE = 16;
constexpr int WORLD_WIDTH_CHUNKS = 8;
constexpr int WORLD_HEIGHT_CHUNKS = 4;
constexpr static phys::Vec2i WORLD_SIZE {WORLD_WIDTH_CHUNKS * CHUNK_SIZE, WORLD_HEIGHT_CHUNKS * CHUNK_SIZE};
constexpr int SEA_LEVEL = WORLD_HEIGHT_CHUNKS * CHUNK_SIZE / 2;
constexpr int CHUNK_COUNT = WORLD_WIDTH_CHUNKS * WORLD_HEIGHT_CHUNKS;

struct Tile {
    Sprite sprite;
};

struct Chunk {
    std::array<Tile, CHUNK_SIZE*CHUNK_SIZE> tiles;

    Tile& getTile(int tileX, int tileY);
};

struct World {
    std::array<Chunk, CHUNK_COUNT> chunks;

    void init();

    Tile& getTileGlobal(int worldX, int worldY);

    Chunk& getChunk(int chunkX, int chunkY);

    [[nodiscard]] static constexpr phys::Vec2i chunkCoords(int chunkIdx) noexcept {
        return { chunkIdx % WORLD_WIDTH_CHUNKS, chunkIdx / WORLD_WIDTH_CHUNKS };
    }

    [[nodiscard]] static constexpr phys::Vec2i tileCoords(int tileIdx) noexcept {
        return { tileIdx % CHUNK_SIZE, tileIdx / CHUNK_SIZE };
    }

    [[nodiscard]] static constexpr phys::Vec2i worldCoords(int chunkIdx, int tileIdx) noexcept {
        auto [chunkX, chunkY] = chunkCoords(chunkIdx);
        auto [tileX,  tileY]  = tileCoords(tileIdx);
        return { chunkX * CHUNK_SIZE + tileX,
                 chunkY * CHUNK_SIZE + tileY };
    }
};


#endif //SANDBOX2D_WORLD_H