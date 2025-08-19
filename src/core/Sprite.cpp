//
// Created by Jacopo Uggeri on 19/08/2025.
//
#include "GameConstants.h"
#include "Sprite.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <filesystem>
#include <ranges>

SDL_Texture* TextureManager::getTexture(const std::string_view textureName, SDL_Renderer* renderer) {
    if (textures.contains(std::string(textureName))) {
        return textures.at(std::string(textureName));
    }
    return loadTexture(textureName, renderer);
}

SDL_Texture* TextureManager::loadTexture(std::string_view textureName, SDL_Renderer* renderer) {
    SDL_Surface* surf = IMG_Load((TEX_PATH / textureName).c_str());
    if (!surf) {
        throw std::runtime_error("Failed to load texture: " + std::string(textureName));
    }

    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    if (!tex) {
        throw std::runtime_error("Failed to create texture: " + std::string(textureName));
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

