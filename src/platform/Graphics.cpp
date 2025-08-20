//
// Created by Jacopo Uggeri on 15/08/2025.
//

#include "Graphics.h"
#include "../game/GameState.h"
#include "../game/resources/TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <format>
#include <iostream>
#include <string_view>
#include <cmath>

bool Graphics::init(const int winW, const int winH, std::string_view windowTitle) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << std::format("SDL_Init error: {}\n", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << std::format("IMG_Init error: {}\n", IMG_GetError());
        return false;
    }

    if (TTF_Init() != 0) {
        std::cerr << std::format("TTF_Init error: {}\n", TTF_GetError());
        return false;
    }

    window_ = SDL_CreateWindow(windowTitle.data(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        winW, winH,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window_) {
        std::cerr << std::format("SDL_CreateWindow error: {}\n", SDL_GetError());
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer_) {
        std::cerr << std::format("SDL_CreateRenderer error: {}\n", SDL_GetError());
        return false;
    }

    if (SDL_RenderSetVSync(renderer_, 1) != 0){
        std::cerr << std::format("Could not set vsync. Error: {}\n", SDL_GetError());
        vsyncEnabled_ = false;
    }

    // Nearest for pixel art
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

    textureManager_.loadTextures(renderer_);
    return true;
}

void Graphics::cameraFollow(const Player& player, double deltaSeconds) {
    const auto dt = static_cast<float>(deltaSeconds);
    constexpr float CAMERA_STIFFNESS = 50.0f;

    const phys::Vec2f toPlayer = player.pos - camera_.pos;
    const float snapFactor = 1.0f - std::exp(-CAMERA_STIFFNESS * dt);
    camera_.pos += toPlayer * snapFactor;
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
    SDL_GetRendererOutputSize(renderer_, &windowWidth, &windowHeight);
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

    if (SDL_Texture* tex = textureManager_.getTexture(sprite.textureName)) {
        SDL_RenderCopyF(renderer_, tex, &srcRect, &destRect);
    } else {
        drawPlaceholder(renderer_, destRect);
    }
}

void Graphics::drawWorld(const GameState& gameState) const {
    for (int chunkIdx = 0; chunkIdx < CHUNK_COUNT; ++chunkIdx) {
        const auto& chunk = gameState.world.chunks[chunkIdx];

        for (int tileIdx = 0; tileIdx < CHUNK_SIZE*CHUNK_SIZE; ++tileIdx) {
            const auto& tile = chunk.tiles[tileIdx];
            if (tile.sprite.textureName.empty()) continue;

            auto screenPos {static_cast<phys::Vec2f>(World::worldCoords(chunkIdx, tileIdx))};
            drawSprite(tile.sprite, screenPos);
        }
    }
}

void Graphics::drawText(std::string_view text, float x, float y) const{
    // fps counter
    if (framesPerSecond_ > 0) {  // Only draw if we have a valid FPS
        static TTF_Font* font = nullptr;
        if (!font) {
            font = TTF_OpenFont("assets/fonts/Hack-Regular.ttf", 16);
            if (!font) {
                std::cerr << "Failed to load font: " << TTF_GetError() << "\n";
                return;
            }
        }

        constexpr SDL_Color color {255, 255, 255, 255};  // White color
        SDL_Surface* textSurface = TTF_RenderText_Blended(font, std::string(text).c_str(), color);

        if (textSurface) {
            if (SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderer_, textSurface)) {
                const SDL_FRect fpsRect {x, y, (float)textSurface->w, (float)textSurface->h};  // Position at (10, 10)
                SDL_RenderCopyF(renderer_, fpsTexture, nullptr, &fpsRect);
                SDL_DestroyTexture(fpsTexture);
            }
            SDL_FreeSurface(textSurface);
        }
    }
}

void Graphics::draw(const GameState& gameState) const {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255); // background black
    SDL_RenderClear(renderer_);

    drawWorld(gameState);
    drawSprite(gameState.player.sprite, gameState.player.pos);

    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);

    if (gameState.paused) {
        // semi-transparent gray overlay
        SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 128);
        int w, h;
        SDL_GetRendererOutputSize(renderer_, &w, &h);
        const SDL_Rect fullscreen = {0, 0, w, h};
        SDL_RenderFillRect(renderer_, &fullscreen);
    }

    const std::string fpsStr = std::format("FPS: {:.0f}", framesPerSecond_);
    drawText(fpsStr, 10, 10);
    drawText(std::format("x: {:.2f}, y: {:.2f}", gameState.player.pos.x, gameState.player.pos.y), 10, 40);

    SDL_RenderPresent(renderer_);
    if (!vsyncEnabled_) {
        SDL_Delay(5); // small throttle to avoid burning CPU if vsync off
    }
}