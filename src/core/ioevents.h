//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef IOEVENTS_H
#define IOEVENTS_H
#pragma once
#include "GameState.h"
#include <SDL2/SDL.h>
#include <format>
#include <iostream>

inline void onKeyDown(GameState& state, const SDL_Keysym* keysym)
{
    switch (keysym->sym)
    {
    case SDLK_q: // quit
        std::cout << std::format("Quit {}\n", state.paused);
        state.running = false;
        break;
    case SDLK_SPACE: // pause
        std::cout << std::format("Pause {}\n", state.paused);
        state.paused = !state.paused;
        break;
    default:;
    }
}

inline void onMouseButtonDown(GameState& gameState, const SDL_MouseButtonEvent* e)
{
    if (e->button == SDL_BUTTON_LEFT) {
        const int mx = e->x;
        const int my = e->y;
        gameState.textureX = mx;
        gameState.textureY = my;
    }
}

inline void handleEvents(GameState& state, SDL_Event* e, SDL_Window* window)
{
    while (SDL_PollEvent(e)) {
        switch (e->type) {
        case SDL_QUIT:
            state.running = false;
            break;
        case SDL_KEYDOWN:
            onKeyDown(state, &e->key.keysym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(state, &e->button);
            break;
        default: ;
        }
    }
}

#endif //IOEVENTS_H
