//
// Created by Jacopo Uggeri on 21/08/2025.
//

#include "game/input/InputManager.h"

bool InputManager::init() {
        return inputSource_.init();
}

void InputManager::handleEvents(GameState &state) {
    inputSource_.handleEvents(state);
    inputSource_.handlePlayerInput(state);
}