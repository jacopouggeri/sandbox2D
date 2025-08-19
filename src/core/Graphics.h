//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef WINDOWING_H
#define WINDOWING_H
#pragma once

#include "GameState.h"
#include "Sprite.h"
#include <SDL2/SDL.h>

struct Graphics {
    SDL_Window* window {nullptr};
    SDL_Renderer* renderer {nullptr};
    TextureManager textureManager {};

    // If successful must be followed by a call to destroy()
    [[nodiscard]] int init(int winW, int winH, const char* windowTitle);

    void destroy() const {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void drawSprite(const Sprite& sprite, const phys::Vec2i& pos);
    void drawTiles(const GameState& gameState);
    void draw(const GameState& gameState);
};

#endif //WINDOWING_H
