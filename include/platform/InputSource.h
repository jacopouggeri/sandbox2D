//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef IOEVENTS_H
#define IOEVENTS_H
#pragma once

#include "game/GameState.h"
#include <SDL.h>

void handleEvents(GameState& state, SDL_Event* e);
void handlePlayerInput(GameState& state);

#endif //IOEVENTS_H
