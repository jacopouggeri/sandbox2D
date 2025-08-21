//
// Created by Jacopo Uggeri on 19/08/2025.
//

#include "platform/sdl/AssetLoader.h"
#include "game/Config.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <filesystem>
#include <iostream>
#include <ranges>

void AssetLoader::loadTextures(SDL_Renderer* renderer)
{
    constexpr std::array essentials = {
        config::resources::PLAYER_TEX, config::resources::WALL_TEX
    };
    for (const auto& tex : essentials) {
        loadTexture(tex, renderer);
    }
}

void AssetLoader::loadTexture(std::string_view textureName, SDL_Renderer* renderer) {
    SDL_Surface* surf = IMG_Load((config::resources::TEX_PATH / textureName).c_str());
    if (!surf) {
        std::cerr << std::format("Failed to load texture with name: {}\n", std::string(textureName));
        return;
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    if (!tex) {
        std::cerr << std::format("Failed to create texture with name: {}", std::string(textureName));
        return;
    }
    // Cache loaded textures
    textures.emplace(textureName, tex);
}

const Texture& AssetLoader::getTexture(std::string_view textureName) const {
    static Texture emptyTexture;
    if (const auto it = textures.find(std::string(textureName)); it != textures.end()) {
        return it->second;
    }
    return emptyTexture;
}

void AssetLoader::loadFonts() {
    constexpr std::array essentials = {config::resources::FONT};
    for (const auto& font : essentials) {
        constexpr int SIZE = 16;
        loadFont(font, SIZE);
    }
}

void AssetLoader::loadFont(std::string_view fontName, int size) {
    TTF_Font* font = TTF_OpenFont((config::resources::FONT_PATH / fontName).c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << "\n";
        return;
    }
    fonts.emplace(fontName, font);
}

const Font& AssetLoader::getFont(std::string_view fontName) const {
    static Font emptyFont;
    if (const auto it = fonts.find(std::string(fontName)); it != fonts.end()) {
        return it->second;
    }
    return emptyFont;
}