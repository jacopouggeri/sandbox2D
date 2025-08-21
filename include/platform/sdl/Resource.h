//
// Created by Jacopo Uggeri on 21/08/2025.
//

#pragma once

#include <SDL_render.h>
#include <SDL_ttf.h>
#include <memory>

template<typename T, auto Deleter>
class Resource {
    using ResourcePtr = std::unique_ptr<T, decltype(Deleter)>;
public:
    explicit Resource(T* resource = nullptr)
        : resource_(resource, Deleter) {}

    explicit operator bool() const { return resource_ != nullptr; }

    [[nodiscard]] T* get() const { return resource_.get(); }

    T* operator->() const { return resource_.get(); }
    T& operator*() const { return *resource_; }

private:
    ResourcePtr resource_;
};

using Texture = Resource<SDL_Texture, &SDL_DestroyTexture>;
using Font = Resource<TTF_Font, &TTF_CloseFont>;
