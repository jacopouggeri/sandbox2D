//
// Created by Jacopo Uggeri on 21/08/2025.
//

#include "game/graphics/Renderer.h"

bool Renderer::init(int winW, int winH, std::string_view windowTitle) {
    if (!graphicsDevice_.init(winW, winH, windowTitle)) return false;
    return true;
}

void Renderer::drawWorld(const World& world) const {
    for (int chunkIdx = 0; chunkIdx < world::CHUNK_COUNT; ++chunkIdx) {
        const auto& chunk = world.chunks[chunkIdx];

        for (int tileIdx = 0; tileIdx < world::CHUNK_SIZE* world::CHUNK_SIZE; ++tileIdx) {
            const auto& tile = chunk.tiles[tileIdx];
            if (tile.sprite.textureName.empty()) continue;

            auto worldPos {static_cast<phys::Vec2f>(World::worldCoords(chunkIdx, tileIdx))};
            drawSprite(tile.sprite, worldPos);
        }
    }
}

void Renderer::cameraSnap(phys::Vec2f pos) {
    camera_.pos = pos;
}

void Renderer::cameraFollow(phys::Vec2f pos, double deltaSeconds) {
    const auto dt = static_cast<float>(deltaSeconds);
    constexpr float CAMERA_STIFFNESS = 50.0f;

    const phys::Vec2f toDestination = pos - camera_.pos;
    const float snapFactor = 1.0f - std::exp(-CAMERA_STIFFNESS * dt);
    camera_.pos += toDestination * snapFactor;
}

phys::Vec2f Renderer::toScreenCoords(const phys::Vec2f &pos) const {
    const auto [windowWidth, windowHeight] = graphicsDevice_.getWindowSize();
    const auto windowSize = static_cast<phys::Vec2f>(phys::Vec2i{windowWidth, windowHeight});
    return (pos - camera_.pos) * config::graphics::TILE_SIZE * config::graphics::DRAW_SCALE + (windowSize / 2.0f);
}

void Renderer::drawDebugInfo(const GameState &gameState, double deltaSeconds) const {
    graphicsDevice_.drawText(std::format("FPS: {:.0f}", 1.0 / deltaSeconds), 10, 10);
    graphicsDevice_.drawText(std::format("x: {:.2f}, y: {:.2f}", gameState.player.pos.x, gameState.player.pos.y), 10, 40);
    graphicsDevice_.drawText(std::format("World Size: {}, {}", world::WORLD_SIZE.x, world::WORLD_SIZE.y), 10, 70);
    graphicsDevice_.drawText(std::format("Game ticks: {}", gameState.gameTicks), 10, 100);
}

void Renderer::render(const GameState& gameState, double deltaSeconds) {
    if (gameState.unpaused()) cameraFollow(gameState.player.pos, deltaSeconds);
    graphicsDevice_.beginFrame();

    drawWorld(gameState.world);
    drawSprite(gameState.player.sprite, gameState.player.pos);

    // semi-transparent gray overlay
    if (gameState.paused) graphicsDevice_.drawOverlay(128, 128, 128, 128);
    // Diagnostics
    if (gameState.debugMode) {
        drawDebugInfo(gameState, deltaSeconds);
    }
    graphicsDevice_.endFrame();
}

void Renderer::drawSprite(const Sprite &sprite, phys::Vec2f pos) const {
    auto [screenX, screenY] = toScreenCoords(pos);
    graphicsDevice_.drawTexture(sprite, screenX, screenY);
}