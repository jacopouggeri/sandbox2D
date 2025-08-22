//
// Created by Jacopo Uggeri on 21/08/2025.
//
#include "platform/sdl/GraphicsDevice.h"

#include "game/Config.h"
#include "game/resources/Sprite.h"

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <format>
#include <iostream>

bool GraphicsDevice::init(int winW, int winH, std::string_view windowTitle) {
    if (!sdlContext_) return false;
    window_ = SDL_CreateWindow(std::string(windowTitle).c_str(),
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
    assetLoader_.loadTextures(renderer_);
    assetLoader_.loadFonts();
    return true;
}

void GraphicsDevice::beginFrame() const {
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255); // background black
    SDL_RenderClear(renderer_);
    SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
}

void GraphicsDevice::endFrame() const {
    SDL_RenderPresent(renderer_);
    if (!vsyncEnabled_) {
        SDL_Delay(5); // small throttle to avoid burning CPU if vsync off
    }
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

void GraphicsDevice::drawText(std::string_view text, float x, float y) const {
    constexpr SDL_Color color {255, 255, 255, 255};
    TTF_Font* font = assetLoader_.getFont(config::resources::FONT).get();
    if (!font) {
        std::cerr << "Font not loaded: " << std::string(config::resources::FONT) << "\n";
        return;
    }
    const std::string textStr{text};
    if (const auto textSurface = TTF_RenderText_Blended(font, textStr.c_str(), color)) {
        if (SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface)) {
            const SDL_FRect textRect {x, y, static_cast<float>(textSurface->w), static_cast<float>(textSurface->h)};
            SDL_RenderCopyF(renderer_, textTexture, nullptr, &textRect);
            SDL_DestroyTexture(textTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

void GraphicsDevice::drawOverlay(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const {
    SDL_SetRenderDrawColor(renderer_, r, g, b, a);
    int w, h;
    SDL_GetRendererOutputSize(renderer_, &w, &h);
    const SDL_Rect fullscreen = {0, 0, w, h};
    SDL_RenderFillRect(renderer_, &fullscreen);
}

std::pair<int, int> GraphicsDevice::getWindowSize() const {
    int windowWidth, windowHeight;
    SDL_GetRendererOutputSize(renderer_, &windowWidth, &windowHeight);
    return {windowWidth, windowHeight};
}

GraphicsDevice::~GraphicsDevice() {
    assetLoader_.clear();
    if (renderer_) {
        SDL_DestroyRenderer(renderer_);
        renderer_ = nullptr;
    }
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
}

void GraphicsDevice::drawTexture(const Sprite &sprite, float screenX, float screenY) const {
    const Texture& texture = assetLoader_.getTexture(sprite.textureName);
    const SDL_Rect srcRect {0, 0, sprite.width, sprite.height};
    const float scaledWidth = sprite.width * config::graphics::DRAW_SCALE;
    const float scaledHeight = sprite.height * config::graphics::DRAW_SCALE;
    screenX -= scaledWidth / 2.0f;
    screenY -= scaledHeight / 2.0f;
    const SDL_FRect destRect {screenX, screenY, scaledWidth, scaledHeight};
    if (SDL_Texture* tex = texture.get()) {
        SDL_RenderCopyF(renderer_, tex, &srcRect, &destRect);
    } else {
        drawPlaceholder(renderer_, destRect);
    }
}
