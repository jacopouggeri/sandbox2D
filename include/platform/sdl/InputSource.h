//
// Created by Jacopo Uggeri on 20/08/2025.
//
#pragma once

struct GameState;

class InputSource final {
public:
    static bool init();
    static void handleEvents(GameState& state);
    static void handlePlayerInput(GameState& state);

    ~InputSource();
};
