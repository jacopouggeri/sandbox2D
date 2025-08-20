//
// Created by Jacopo Uggeri on 20/08/2025.
//

#ifndef SANDBOX2D_GAMESTATE_H
#define SANDBOX2D_GAMESTATE_H
#include "Player.h"
#include "world/World.h"

struct GameState {
    bool running = true;
    bool paused = true;
    Player player;
    World world;
};

#endif //SANDBOX2D_GAMESTATE_H