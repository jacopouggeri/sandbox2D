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
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};
    TextureManager textureManager {};
    double framesPerSecond {};

public:
    Graphics() = default;
    ~Graphics() { destroy(); }

    // Delete copy operations
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    [[nodiscard]] bool init(int winW, int winH, std::string_view windowTitle);
    void destroy() noexcept {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
        IMG_Quit();
        SDL_Quit();
    }

    void draw(const GameState& gameState) const;
    void cameraFollow(const Player& player) { camera_.pos = player.pos; }
    void setFPS(double fps) { this->framesPerSecond = fps; }

private:
    class Camera { public: phys::Vec2f pos {}; } camera_;

    [[nodiscard]] phys::Vec2f toScreenCoords(const phys::Vec2f& v) const;
    void drawSprite(const Sprite& sprite, const phys::Vec2f& pos) const;
    void drawWorld(const GameState& gameState) const;
    void drawText(std::string_view text, int x, int y) const;
};

#endif //WINDOWING_H
