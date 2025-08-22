//
// Created by Jacopo Uggeri on 15/08/2025.
//
#pragma once

#include "physics/Vec2.h"
#include <filesystem>
#include <string_view>

namespace config {

inline constexpr std::string_view GAME_NAME {"Sandbox 2D"};

    namespace resources {
        // resources (should move in namespace or a more relevant file later)
        inline const std::filesystem::path ASSETS_PATH = "assets";
        inline const std::filesystem::path TEX_PATH = ASSETS_PATH / "textures";
        inline const std::filesystem::path FONT_PATH = ASSETS_PATH / "fonts";
        inline constexpr std::string_view FONT {"Hack-Regular.ttf"};
        inline constexpr std::string_view PLAYER_TEX {"bacon.png"};
        inline constexpr std::string_view WALL_TEX {"wall.png"};
    }

    namespace graphics {
        // graphics (should move in namespace or a more relevant file later)
        inline constexpr phys::Vec2i WINDOW_SIZE {1280, 720};
        inline constexpr int TILE_SIZE = 16;
        inline constexpr float DRAW_SCALE = 4.0;
    }

}