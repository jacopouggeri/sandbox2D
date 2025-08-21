//
// Created by Jacopo Uggeri on 21/08/2025.
//

#include "game/input/InputManager.h"

bool InputManager::init() const {
        return inputSource_.init();
}

void InputManager::handleEvents(GameState &state) const {
    inputSource_.handleEvents(state);
    inputSource_.handlePlayerInput(state);
}