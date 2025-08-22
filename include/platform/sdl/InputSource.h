//
// Created by Jacopo Uggeri on 20/08/2025.
//
#pragma once

struct GameState;

class InputSource final {
public:
    bool init();
    void handleEvents(GameState& state);
    void handlePlayerInput(GameState& state);

    ~InputSource();
};
