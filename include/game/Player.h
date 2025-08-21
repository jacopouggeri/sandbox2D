//
// Created by Jacopo Uggeri on 20/08/2025.
//
#pragma once
#include "game/Config.h"
#include "physics/DynamicBody.h"
#include "physics/Vec2.h"
#include "world/World.h"

class Player {
public:
    void step(double deltaSeconds);
    phys::DynamicBody& getBody() { return body_; }

private:
    phys::DynamicBody body_ {0.5, 0.3};

public:
    Sprite sprite {std::string(config::resources::PLAYER_TEX)};
    phys::Vec2f& pos {body_.position};
    phys::Vec2f direction {};
    mutable phys::Vec2f targetDirection {};
};