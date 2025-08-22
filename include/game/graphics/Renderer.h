//
// Created by Jacopo Uggeri on 21/08/2025.
//
#pragma once
#include "game/GameState.h"
#include "platform/sdl/GraphicsDevice.h"

class Renderer {
public:
    bool init(int winW, int winH, std::string_view windowTitle);
    void render(const GameState& gameState, double deltaSeconds);

private:
    void drawSprite(const Sprite &sprite, phys::Vec2f pos) const;
    void drawWorld(const World& world) const;
    void cameraSnap(phys::Vec2f pos);
    void cameraFollow(phys::Vec2f pos, double deltaSeconds);
    phys::Vec2f toScreenCoords(const phys::Vec2f& pos) const;
    void drawDebugInfo(const GameState &gameState, double deltaSeconds) const;

    GraphicsDevice graphicsDevice_ {};
    struct Camera { phys::Vec2f pos {0, 0}; } camera_;
};