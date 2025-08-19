//
// Created by Jacopo Uggeri on 15/08/2025.
//
#include "GameConstants.h"
#include "GameState.h"
#include "Graphics.h"
#include "resources/TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <format>
#include <iostream>
#include <string_view>

bool Graphics::init(const int winW, const int winH, const std::string_view& windowTitle) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << std::format("SDL_Init error: %s\n", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        std::cerr << "IMG Init Error: " << IMG_GetError() << "\n";
        return false;
    }

    window = SDL_CreateWindow(windowTitle.data(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        winW, winH,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << std::format("SDL_CreateWindow error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << std::format("SDL_CreateRenderer error: %s\n", SDL_GetError());
        return false;
    }

    textureManager.loadTextures(renderer);
    return true;
}

// Visible fallback (magenta box) if texture missing
static void drawPlaceholder(SDL_Renderer* r, const SDL_Rect& rct) {
    const int hw = rct.w/2, hh = rct.h/2;
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRect(r, &rct);
    SDL_SetRenderDrawColor(r, 255, 0, 255, 255);
    const SDL_Rect q[] = {
        {rct.x, rct.y, hw, hh}, {rct.x + hw, rct.y + hh, rct.w - hw, rct.h - hh}
    };
    SDL_RenderFillRects(r, q, 2);
}

void Graphics::drawSprite(const Sprite& sprite, const phys::Vec2i& pos) const {
    auto [x, y] = pos;
    const int scaledWidth {static_cast<int>(static_cast<float>(sprite.width) * SPRITE_SCALE)};
    const int scaledHeight {static_cast<int>(static_cast<float>(sprite.height) * SPRITE_SCALE)};
    const SDL_Rect srcRect {0, 0, sprite.width, sprite.height};
    const SDL_Rect destRect {x - scaledWidth / 2, y - scaledHeight / 2, scaledWidth, scaledHeight};

    if (SDL_Texture* tex = textureManager.getTexture(sprite.textureName)) {
        SDL_RenderCopy(renderer, tex, &srcRect, &destRect);
    } else {
        drawPlaceholder(renderer, destRect);
    }
}

void Graphics::drawTiles(const GameState& gameState) const {
    for (const auto& [sprite, pos] : gameState.tiles) {
        drawSprite(sprite, pos);
    }
}

void Graphics::draw(const GameState& gameState) const {
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