//
// Created by Jacopo Uggeri on 15/08/2025.
//
#include "CONST.h"
#include "GameState.h"
#include "Graphics.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <format>
#include <iostream>

int Graphics::init(const int winW, const int winH, const char* windowTitle)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << std::format("SDL_Init error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG Init Error: " << IMG_GetError() << "\n";
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow(windowTitle,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        winW, winH,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << std::format("SDL_CreateWindow error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << std::format("SDL_CreateRenderer error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    const std::filesystem::path texture_path = TEX_PATH / "placeholder.png";
    if (loadTexture(texture_path) == EXIT_FAILURE) {
        std::cerr << "Failed to load texture from: " << texture_path << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int Graphics::loadTexture(const std::filesystem::path& texturePath)
{
    SDL_Surface* surface = IMG_Load(texturePath.c_str());
    if (!surface) {
        std::cerr << "SDL_LoadBMP Error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Texture creation error: " << SDL_GetError() << "\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void draw(const Graphics& graphics, const GameState& gameState)
{
    SDL_SetRenderDrawColor(graphics.renderer, 0, 0, 0, 255); // background black
    SDL_RenderClear(graphics.renderer);

    constexpr int tw = 16;
    constexpr int cols = 144 / tw;
    constexpr int tx = (36 % cols) * tw;
    constexpr int ty = (36/ cols) * tw;
    constexpr int atw = 3 * tw;

    constexpr SDL_Rect sourceRect { tx, ty, tw, tw };
    phys::Vec2i playerPos = gameState.player.pos_i();
    const SDL_Rect destRect {playerPos.x - atw / 2, playerPos.y - atw / 2, atw, atw};
    SDL_RenderCopy(graphics.renderer, graphics.texture, &sourceRect, &destRect);

    SDL_SetRenderDrawBlendMode(graphics.renderer, SDL_BLENDMODE_BLEND);

    // after your normal draw calls:
    if (gameState.paused) {
        // semi-transparent sepia overlay
        SDL_SetRenderDrawColor(graphics.renderer, 0x99, 0x66, 0x33, 0x80);
        int w, h;
        SDL_GetRendererOutputSize(graphics.renderer, &w, &h);
        const SDL_Rect fullscreen = {0, 0, w, h};
        SDL_RenderFillRect(graphics.renderer, &fullscreen);
    }

    SDL_RenderPresent(graphics.renderer);
    SDL_Delay(5); // small throttle to avoid burning CPU if vsync off
}