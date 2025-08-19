//
// Created by Jacopo Uggeri on 15/08/2025.
//
#include "GameConstants.h"
#include "GameState.h"
#include "Graphics.h"
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <format>
#include <iostream>

int Graphics::init(const int winW, const int winH, const char* windowTitle) {
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << std::format("SDL_CreateRenderer error: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void Graphics::drawSprite(const Sprite& sprite, const phys::Vec2i& pos) {
    auto [x, y] = pos;
    const int scaledWidth = sprite.width * SPRITE_SCALE;
    const int scaledHeight = sprite.height * SPRITE_SCALE;
    const SDL_Rect srcRect {0, 0, sprite.width, sprite.height};
    const SDL_Rect destRect {x - scaledWidth / 2, y - scaledHeight / 2, scaledWidth, scaledHeight};
    SDL_RenderCopy(renderer, textureManager.getTexture(sprite.textureName, renderer), &srcRect, &destRect);
}

void Graphics::drawTiles(const GameState& gameState)
{
    for (const auto& [sprite, pos] : gameState.tiles) {
        drawSprite(sprite, pos);
    }
}

void Graphics::draw(const GameState& gameState) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // background black
    SDL_RenderClear(renderer);

    drawSprite(gameState.player.sprite, gameState.player.pos_i());
    drawTiles(gameState);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (gameState.paused) {
        // semi-transparent sepia overlay
        SDL_SetRenderDrawColor(renderer, 0x99, 0x66, 0x33, 0x80);
        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h);
        const SDL_Rect fullscreen = {0, 0, w, h};
        SDL_RenderFillRect(renderer, &fullscreen);
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(5); // small throttle to avoid burning CPU if vsync off
}
