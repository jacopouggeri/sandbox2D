//
// Created by Jacopo Uggeri on 21/08/2025.
//

#include "platform/sdl/InputSource.h"
#include "game/GameState.h"

#include <SDL.h>
#include <format>
#include <iostream>

bool InputSource::init() {
    if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0) {
        std::cerr << std::format("SDL_INIT_EVENTS error: {}\n", SDL_GetError());
        return false;
    }
    return true;
}


void onKeyDown(GameState &state, const SDL_Keysym *keysym) {
    switch (keysym->sym) {
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

void onMouseButtonDown(GameState& gameState, const SDL_MouseButtonEvent* e) {
    if (e->button == SDL_BUTTON_LEFT && e->state == SDL_PRESSED) {
        const int mx = e->x;
        const int my = e->y;
        gameState.player.pos = {static_cast<float>(mx), static_cast<float>(my)};
    }
}

void onMouseMotion(GameState& gameState, const SDL_MouseMotionEvent* e)
{
    if (e->state & SDL_BUTTON_LMASK) {
        const int mx = e->x;
        const int my = e->y;
        gameState.player.pos = {static_cast<float>(mx), static_cast<float>(my)};
    }
}

void InputSource::handleEvents(GameState &state) {
    SDL_Event e;
    SDL_Event* ePtr = &e;
    while (SDL_PollEvent(ePtr)) {
        switch (ePtr->type) {
        case SDL_QUIT:
            state.running = false;
            break;
        case SDL_KEYDOWN:
            onKeyDown(state, &ePtr->key.keysym);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(state, &ePtr->button);
            break;
        case SDL_MOUSEMOTION:
            onMouseMotion(state, &ePtr->motion);
            break;
        default: ;
        }
    }
}

void InputSource::handlePlayerInput(GameState &state) {
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    float dx = 0, dy = 0;
    if (keyState[SDL_SCANCODE_W]) dy -= 1;
    if (keyState[SDL_SCANCODE_S]) dy += 1;
    if (keyState[SDL_SCANCODE_A]) dx -= 1;
    if (keyState[SDL_SCANCODE_D]) dx += 1;

    // normalize for diagonals
    if (const float len = std::sqrt(dx*dx + dy*dy); len > 0) {
        dx /= len;
        dy /= len;
    }

    state.player.set_velocity({dx , dy});
}

InputSource::~InputSource() {
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
}