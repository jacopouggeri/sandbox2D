//
// Created by Jacopo Uggeri on 19/08/2025.
//

#include "../Config.h"
#include "TextureManager.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <iostream>
#include <ranges>

TextureManager::~TextureManager() {
    for (const auto& tex : textures | std::views::values) {
        SDL_DestroyTexture(tex);
    }
}

void TextureManager::loadTextures(SDL_Renderer* renderer)
{
    const std::vector essentials = {
        PLAYER_TEX, WALL_TEX
    };
    for (const auto& tex : essentials) {
        loadTexture(tex, renderer);
    }
}

void TextureManager::loadTexture(std::string_view textureName, SDL_Renderer* renderer) {
    SDL_Surface* surf = IMG_Load((TEX_PATH / textureName).c_str());
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

SDL_Texture* TextureManager::getTexture(std::string_view textureName) const {
    if (const auto it = textures.find(std::string(textureName)); it != textures.end()) {
        return it->second;
    }
    return nullptr;
}