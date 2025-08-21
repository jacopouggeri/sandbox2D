//
// Created by Jacopo Uggeri on 20/08/2025.
//
#pragma once

#include "game/resources/Sprite.h"
#include "platform/sdl/AssetLoader.h"
#include "platform/sdl/SDLContext.h"
#include <SDL_render.h>
#include <SDL_video.h>
#include <string_view>

class GraphicsDevice final {
public:
    bool init(int winW, int winH, std::string_view windowTitle);
    void beginFrame() const;
    void endFrame() const;
    void drawTexture(const Sprite &sprite, float screenX, float screenY) const;
    void drawText(std::string_view text, float x, float y) const;
    void drawOverlay(uint8_t r, uint8_t g, uint8_t b, uint8_t a) const;
    std::pair<int, int> getWindowSize() const;

private:
    SDLContext sdlContext_ {};
    SDL_Window* window_ = nullptr;
    SDL_Renderer* renderer_ = nullptr;
    AssetLoader assetLoader_ {};
    bool vsyncEnabled_ = true;

public:
    ~GraphicsDevice();
};
