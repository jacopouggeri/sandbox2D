//
// Created by Jacopo Uggeri on 21/08/2025.
//

#pragma once
#include "platform/sdl/InputSource.h"

class InputManager {
public:
    bool init() const;
    void handleEvents(GameState& state) const;

private:
    InputSource inputSource_;
};