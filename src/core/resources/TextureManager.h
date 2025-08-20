//
// Created by Jacopo Uggeri on 19/08/2025.
//

#ifndef SANDBOX2D_SPRITE_H
#define SANDBOX2D_SPRITE_H
#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <string_view>
#include <unordered_map>

#include "../GameConstants.h"

struct Sprite {
    std::string textureName;
    int width {static_cast<int>(16 * DRAW_SCALE)};
    int height {static_cast<int>(16 * DRAW_SCALE)};
};

class TextureManager {
public:
    TextureManager() = default;
    ~TextureManager();

    // Prevent copying
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    void loadTextures(SDL_Renderer* renderer);
    [[nodiscard]] SDL_Texture* getTexture(std::string_view textureName) const;

private:
    void loadTexture(std::string_view textureName, SDL_Renderer* renderer);

    std::unordered_map<std::string, SDL_Texture*> textures;
};

#endif //SANDBOX2D_SPRITE_H