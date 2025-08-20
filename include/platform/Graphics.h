//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef GRAPHICS_H
#define GRAPHICS_H
#pragma once

#include "game/GameState.h"
#include "game/Player.h"
#include "game/resources/TextureManager.h"

#include <SDL.h>
#include <string_view>

class Graphics {

public:
    [[nodiscard]] bool init(int winW, int winH, std::string_view windowTitle);

    void draw(const GameState& gameState) const;
    void cameraSnap(const Player& player) { camera_.pos = player.pos; }
    void cameraFollow(const Player& player, double deltaSeconds);
    void setFPS(double fps) { this->framesPerSecond_ = fps; }

private:
    SDL_Window* window_ {nullptr};
    SDL_Renderer* renderer_ {nullptr};
    TextureManager textureManager_ {};
    double framesPerSecond_ {};
    bool vsyncEnabled_ {true};
    class Camera { public: phys::Vec2f pos {}; } camera_;

    void destroy() noexcept;
    [[nodiscard]] phys::Vec2f toScreenCoords(const phys::Vec2f& v) const;
    void drawSprite(const Sprite& sprite, const phys::Vec2f& pos) const;
    void drawWorld(const GameState& gameState) const;
    void drawText(std::string_view text, float x, float y) const;

public:
    Graphics() = default;
    ~Graphics() { destroy(); }

    // Delete copy operations
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    // Delete move operations
    Graphics(Graphics&&) = delete;
    Graphics& operator=(Graphics&&) = delete;
};

#endif //GRAPHICS_H
