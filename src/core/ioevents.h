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

inline void onKeyDown(GameState& state, const SDL_Keysym* keysym) {
    switch (keysym->sym) {
    case SDLK_q: // quit
        std::cout << std::format("Quit {}\n", state.paused);
        state.running = false;
        break;
    case SDLK_w: // UP
        state.playerPos.y -= 10;
        break;
    case SDLK_s: // DOWN
        state.playerPos.y += 10;
        break;
    case SDLK_a: // LEFT
        state.playerPos.x -= 10;
        break;
    case SDLK_d: // RIGHT
        state.playerPos.x += 10;
        break;
    case SDLK_SPACE: // pause
        std::cout << std::format("Pause {}\n", state.paused);
        state.paused = !state.paused;
        break;
    default:;
    }
}

inline void onMouseButtonDown(GameState& gameState, const SDL_MouseButtonEvent* e) {
    if (e->button == SDL_BUTTON_LEFT && e->state == SDL_PRESSED) {
        const int mx = e->x;
        const int my = e->y;
        gameState.playerPos.x = mx;
        gameState.playerPos.y = my;
    }
}

inline void onMouseMotion(GameState& gameState, const SDL_MouseMotionEvent* e) {
    if (e->state & SDL_BUTTON_LMASK) {
        const int mx = e->x;
        const int my = e->y;
        gameState.playerPos.x = mx;
        gameState.playerPos.y = my;
    }
}

inline void handleEvents(GameState& state, SDL_Event* e, SDL_Window* window) {
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
        case SDL_MOUSEMOTION:
            onMouseMotion(state, &e->motion);
            break;
        default: ;
        }
    }
}

#endif //IOEVENTS_H
