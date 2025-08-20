//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef CONST_H
#define CONST_H
#pragma once

#include "physics/Vec2.h"
#include <string_view>
#include <filesystem>

inline constexpr std::string_view GAME_NAME {"Sandbox 2D"};

// resources (should move in namespace or a more relevant file later)
inline const std::filesystem::path ASSETS_PATH = "assets";
inline const std::filesystem::path TEX_PATH = ASSETS_PATH / "textures";
inline constexpr std::string_view PLAYER_TEX {"bacon.png"};
inline constexpr std::string_view WALL_TEX {"wall.png"};

// graphics (should move in namespace or a more relevant file later)
inline constexpr phys::Vec2i WINDOW_SIZE {1280, 720};
inline constexpr float DRAW_SCALE = 4.0;

#endif //CONST_H
