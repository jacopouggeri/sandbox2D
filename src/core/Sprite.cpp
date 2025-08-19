//
// Created by Jacopo Uggeri on 19/08/2025.
//
#include "GameConstants.h"
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <iostream>
#include <ranges>

void TextureManager::load(SDL_Renderer* renderer)
{
    const std::vector essentials = {
        PLACEHOLDER_TEX, PLAYER_TEX, WALL_TEX
    };
    for (const auto& tex : essentials) {
        loadTexture(tex, renderer);
    }
}

SDL_Texture* TextureManager::getTexture(const std::string_view textureName) {
    if (const auto it = textures.find(std::string(textureName)); it != textures.end()) {
        return it->second;
    }
    if (const auto it = textures.find(std::string(PLACEHOLDER_TEX)); it != textures.end()) {
        std::cerr << std::format("Failed to load texture with name: {}\n", std::string(textureName));
        return it->second;
    }
    std::cerr << std::format("Failed to load placeholder texture with name: {}\n", std::string(textureName));
    return nullptr;
}

SDL_Texture* TextureManager::loadTexture(std::string_view textureName, SDL_Renderer* renderer) {
    SDL_Surface* surf = IMG_Load((TEX_PATH / textureName).c_str());
    if (!surf) {
        std::cerr << std::format("Failed to load texture with name: {}\n", std::string(textureName));
        return getTexture(PLACEHOLDER_TEX);
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    if (!tex) {
        std::cerr << std::format("Failed to create texture with name: {}", std::string(textureName));
        return getTexture(PLACEHOLDER_TEX);
    }

    // insert into cache
    textures.emplace(textureName, tex);
    return tex;
}

TextureManager::~TextureManager() {
    for (const auto& tex : textures | std::views::values) {
        SDL_DestroyTexture(tex);
    }
}