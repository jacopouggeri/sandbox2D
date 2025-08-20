//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef WINDOWING_H
#define WINDOWING_H
#pragma once

#include "GameState.h"
#include "resources/TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string_view>

class Graphics {
    SDL_Window* window_ {nullptr};
    SDL_Renderer* renderer_ {nullptr};
    TextureManager textureManager_ {};
    double framesPerSecond_ {};
    bool vsyncEnabled_ {true};

public:
    Graphics() = default;
    ~Graphics() { destroy(); }

    // Delete copy operations
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    [[nodiscard]] bool init(int winW, int winH, std::string_view windowTitle);
    void destroy() noexcept {
        if (renderer_) {
            SDL_DestroyRenderer(renderer_);
            renderer_ = nullptr;
        }
        if (window_) {
            SDL_DestroyWindow(window_);
            window_ = nullptr;
        }
        IMG_Quit();
        SDL_Quit();
    }

    void draw(const GameState& gameState) const;
    void cameraSnap(const Player& player) { camera_.pos = player.pos; }
    void cameraFollow(const Player& player, double deltaSeconds);
    void setFPS(double fps) { this->framesPerSecond_ = fps; }

private:
    class Camera { public: phys::Vec2f pos {}; } camera_;

    [[nodiscard]] phys::Vec2f toScreenCoords(const phys::Vec2f& v) const;
    void drawSprite(const Sprite& sprite, const phys::Vec2f& pos) const;
    void drawWorld(const GameState& gameState) const;
    void drawText(std::string_view text, float x, float y) const;
};

#endif //WINDOWING_H
