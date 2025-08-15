//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef GAMESTATE_H
#define GAMESTATE_H
#pragma once

struct GameState {
    bool running = true;
    bool paused = true;
    int textureX = 0; // X position of the texture in the window
    int textureY = 0; // Y position of the texture in the window
};

#endif //GAMESTATE_H
