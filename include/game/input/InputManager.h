//
// Created by Jacopo Uggeri on 21/08/2025.
//

#pragma once
#include "platform/sdl/InputSource.h"

class InputManager {
public:
    bool init();
    void handleEvents(GameState& state);

private:
    InputSource inputSource_;
};