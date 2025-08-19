//
// Created by Jacopo Uggeri on 15/08/2025.
//
#include "GameConstants.h"
#include "GameState.h"
#include "Graphics.h"
#include "resources/TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <format>
#include <iostream>
#include <string_view>
#include <cmath>

bool Graphics::init(const int winW, const int winH, std::string_view windowTitle) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << std::format("SDL_Init error: %s\n", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG Init Error: " << IMG_GetError() << "\n";
        return false;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF Init Error: " << TTF_GetError() << "\n";
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

    if (SDL_RenderSetVSync(renderer, 1) != 0){
        std::cerr << std::format("Could not set vsync. Error: %s\n", SDL_GetError());
    }

    // Nearest for pixel art
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    textureManager.loadTextures(renderer);
    return true;
}

// Visible fallback (magenta box) if texture missing
static void drawPlaceholder(SDL_Renderer* r, const SDL_FRect& rct) {
    const float hw = rct.w/2, hh = rct.h/2;
    SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
    SDL_RenderFillRectF(r, &rct);
    SDL_SetRenderDrawColor(r, 255, 0, 255, 255);
    const SDL_FRect q[] = {
        {rct.x, rct.y, hw, hh}, {rct.x + hw, rct.y + hh, rct.w - hw, rct.h - hh}
    };
    SDL_RenderFillRectsF(r, q, 2);
}

phys::Vec2f Graphics::toScreenCoords(const phys::Vec2f& v) const {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    const auto windowSize = static_cast<phys::Vec2f>(phys::Vec2i{windowWidth, windowHeight});
    return (v - camera_.pos) * TILE_SIZE + (windowSize / 2.0f);
}

void Graphics::drawSprite(const Sprite& sprite, const phys::Vec2f& pos) const
{
    const SDL_Rect srcRect {0, 0, sprite.width, sprite.height};
    phys::Vec2f screenPos = toScreenCoords(pos);
    screenPos -= phys::Vec2f{static_cast<float>(sprite.width) / 2.0f, static_cast<float>(sprite.height) / 2.0f};
    const auto screenX = screenPos.x;
    const auto screenY = screenPos.y;
    const SDL_FRect destRect {screenX, screenY, (float)sprite.width, (float)sprite.height};

    if (SDL_Texture* tex = textureManager.getTexture(sprite.textureName)) {
        SDL_RenderCopyF(renderer, tex, &srcRect, &destRect);
    } else {
        drawPlaceholder(renderer, destRect);
    }
}

void Graphics::drawWorld(const GameState& gameState) const {
    for (int chunkIdx = 0; chunkIdx < CHUNK_COUNT; ++chunkIdx) {
        const auto& chunk = gameState.world.chunks[chunkIdx];

        for (int tileIdx = 0; tileIdx < CHUNK_SIZE*CHUNK_SIZE; ++tileIdx) {
            const auto& tile = chunk.tiles[tileIdx];
            if (tile.sprite.textureName.empty()) continue;

            auto [worldX, worldY] = World::worldCoords(chunkIdx, tileIdx);
            auto screenX = static_cast<float>(worldX);
            auto screenY = static_cast<float>(worldY);
            drawSprite(tile.sprite, {screenX, screenY});
        }
    }
}

void Graphics::drawText(std::string_view text, float x, float y) const{
    // fps counter
    if (framesPerSecond > 0) {  // Only draw if we have a valid FPS
        static TTF_Font* font = nullptr;
        if (!font) {
            font = TTF_OpenFont("assets/fonts/Hack-Regular.ttf", 16);
            if (!font) {
                std::cerr << "Failed to load font: " << TTF_GetError() << "\n";
                return;
            }
        }

        constexpr SDL_Color color {255, 255, 255, 255};  // White color
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.data(), color);

        if (textSurface) {
            if (SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderer, textSurface)) {
                const SDL_FRect fpsRect {x, y, (float)textSurface->w, (float)textSurface->h};  // Position at (10, 10)
                SDL_RenderCopyF(renderer, fpsTexture, nullptr, &fpsRect);
                SDL_DestroyTexture(fpsTexture);
            }
            SDL_FreeSurface(textSurface);
        }
    }
}

void Graphics::draw(const GameState& gameState) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // background black
    SDL_RenderClear(renderer);

    drawWorld(gameState);
    drawSprite(gameState.player.sprite, gameState.player.pos);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    if (gameState.paused) {
        // semi-transparent gray overlay
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 128);
        int w, h;
        SDL_GetRendererOutputSize(renderer, &w, &h);
        const SDL_Rect fullscreen = {0, 0, w, h};
        SDL_RenderFillRect(renderer, &fullscreen);
    }

    const std::string fpsStr = std::to_string(static_cast<int>(framesPerSecond));
    drawText(fpsStr, 10, 10);
    drawText(std::format("x: {:.2f}, y: {:.2f}", gameState.player.pos.x, gameState.player.pos.y), 10, 40);

    SDL_RenderPresent(renderer);
    if (SDL_GetHint(SDL_HINT_RENDER_VSYNC) == nullptr) {
        SDL_Delay(5); // small throttle to avoid burning CPU if vsync off
    }
}