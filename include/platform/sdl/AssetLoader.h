//
// Created by Jacopo Uggeri on 19/08/2025.
//
#pragma once

#include "platform/sdl/Resource.h"
#include <string>
#include <string_view>
#include <unordered_map>

class AssetLoader {
public:
    void loadTextures(SDL_Renderer* renderer);
    void loadFonts();
    [[nodiscard]] const Texture& getTexture(std::string_view textureName) const noexcept;
    [[nodiscard]] const Font& getFont(std::string_view fontName) const noexcept;
    void clear() noexcept {
        textures.clear();
        fonts.clear();
    }

private:
    void loadTexture(std::string_view textureName, SDL_Renderer* renderer);
    void loadFont(std::string_view fontName, int size);

    std::unordered_map<std::string, Texture> textures;
    std::unordered_map<std::string, Font> fonts;

public:
    AssetLoader() = default;
    ~AssetLoader() = default;
    // Prevent copying
    AssetLoader(const AssetLoader&) = delete;
    AssetLoader& operator=(const AssetLoader&) = delete;
};