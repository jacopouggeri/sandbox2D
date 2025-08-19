//
// Created by Jacopo Uggeri on 15/08/2025.
//

#ifndef CONST_H
#define CONST_H
#pragma once
#include <string>
#include <filesystem>

inline const std::string GAME_NAME = "Sandbox 2D";
inline const std::filesystem::path ASSETS_PATH = "assets";
inline const std::filesystem::path TEX_PATH = ASSETS_PATH / "textures";
inline constexpr std::string PLAYER_TEX = "bacon.png";
inline constexpr std::string WALL_TEX = "wall.png";
inline constexpr int SPRITE_SCALE = 3;

#endif //CONST_H
