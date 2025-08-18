//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once
#include "physics/Vec2.h"

struct GameState {
    bool running = true;
    bool paused = true;
    phys::Vec2i playerPos;
};

#endif //GAMESTATE_H
