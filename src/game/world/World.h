//
// Created by Jacopo Uggeri on 19/08/2025.
//

#ifndef SANDBOX2D_WORLD_H
#define SANDBOX2D_WORLD_H
#pragma once

#include "../Config.h"
#include "../resources/TextureManager.h"
#include <array>
#include <iostream>

constexpr int TILE_SIZE = 16 * DRAW_SCALE;
constexpr int CHUNK_SIZE = 16;
constexpr int WORLD_WIDTH_CHUNKS = 8;
constexpr int WORLD_HEIGHT_CHUNKS = 4;
constexpr int SEA_LEVEL = WORLD_HEIGHT_CHUNKS * CHUNK_SIZE / 2;
constexpr int CHUNK_COUNT = WORLD_WIDTH_CHUNKS * WORLD_HEIGHT_CHUNKS;

struct Tile {
    Sprite sprite;
};

struct Chunk {
    std::array<Tile, CHUNK_SIZE*CHUNK_SIZE> tiles;

    Tile& getTile(int tileX, int tileY) {
        if (tileX < 0 || tileX >= CHUNK_SIZE || tileY < 0 || tileY >= CHUNK_SIZE) {
            std::cerr << "Invalid tile access: (" << tileX << ", " << tileY << ")" << std::endl;
            throw std::out_of_range("Invalid tile access");
        }
        return tiles[tileY*CHUNK_SIZE + tileX];
    }
};

struct World {
    std::array<Chunk, CHUNK_COUNT> chunks;

    void init() {
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

    Tile& getTileGlobal(int worldX, int worldY) {
        const int chunkX = worldX / CHUNK_SIZE;
        const int chunkY = worldY / CHUNK_SIZE;
        const int tileX  = worldX % CHUNK_SIZE;
        const int tileY  = worldY % CHUNK_SIZE;
        return getChunk(chunkX, chunkY).getTile(tileX, tileY);
    }

    Chunk& getChunk(int chunkX, int chunkY) {
        if (chunkX < 0 || chunkX >= WORLD_WIDTH_CHUNKS || chunkY < 0 || chunkY >= WORLD_HEIGHT_CHUNKS) {
            std::cerr << "Invalid chunk access: (" << chunkX << ", " << chunkY << ")" << std::endl;
            throw std::out_of_range("Invalid chunk access");
        }
        return chunks[chunkY*WORLD_WIDTH_CHUNKS + chunkX];
    }

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