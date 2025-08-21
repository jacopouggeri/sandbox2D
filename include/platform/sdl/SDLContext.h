//
// Created by Jacopo Uggeri on 21/08/2025.
//

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <format>
#include <iostream>

class SDLContext {
    bool initialized = false;

public:
    SDLContext() {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << std::format("SDL_Init error: {}\n", SDL_GetError());
            return;
        }
        if (IMG_Init(IMG_INIT_PNG) == 0) {
            std::cerr << std::format("IMG_Init error: {}\n", IMG_GetError());
            return;
        }

        if (TTF_Init() != 0) {
            std::cerr << std::format("TTF_Init error: {}\n", TTF_GetError());
            return;
        }
        initialized = true;
    }

    ~SDLContext() {
        if (initialized) {
            TTF_Quit();
            IMG_Quit();
            SDL_Quit();
        }
    }

    explicit operator bool() const { return initialized; }

    // Prevent copying
    SDLContext(const SDLContext&) = delete;
    SDLContext& operator=(const SDLContext&) = delete;
};