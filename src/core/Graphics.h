//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef WINDOWING_H
#define WINDOWING_H
#pragma once
#include "GameState.h"
#include <filesystem>
#include <SDL2/SDL.h>

struct Graphics {
    SDL_Window* window {};
    SDL_Renderer* renderer {};
    SDL_Texture* texture {}; // For now, a single texture

    // If successful must be followed by a call to destroy()
    [[nodiscard]] int init(int winW, int winH, const char* windowTitle);

    void destroy() const {
        if (renderer) SDL_DestroyRenderer(renderer);
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

    void draw( const GameState& gameState) const;

private:
    [[nodiscard]] int loadTexture(const std::filesystem::path& texturePath);

};

#endif //WINDOWING_H
