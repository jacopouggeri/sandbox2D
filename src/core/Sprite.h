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

struct Sprite {
    std::string textureName;
    int width {16};
    int height {16};
};

class TextureManager {
public:
    TextureManager() = default;
    ~TextureManager();

    void load(SDL_Renderer* renderer);
    SDL_Texture* getTexture(std::string_view textureName);

private:
    SDL_Texture* loadTexture(std::string_view textureName, SDL_Renderer* renderer);

    std::unordered_map<std::string, SDL_Texture*> textures;
};

#endif //SANDBOX2D_SPRITE_H