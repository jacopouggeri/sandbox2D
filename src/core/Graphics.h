//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef WINDOWING_H
#define WINDOWING_H
#pragma once

#include "GameState.h"
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <string_view>

class Graphics {
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};
    TextureManager textureManager {};

public:
    Graphics() = default;
    ~Graphics() { destroy(); }

    // Delete copy operations
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;

    [[nodiscard]] bool init(int winW, int winH, const std::string_view& windowTitle);
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

    void drawSprite(const Sprite& sprite, const phys::Vec2i& pos) const;
    void drawTiles(const GameState& gameState) const;
    void draw(const GameState& gameState);
};

#endif //WINDOWING_H
