//
// Created by Jacopo Uggeri on 16/08/2025.
//

#ifndef SANDBOX2D_VEC2_H
#define SANDBOX2D_VEC2_H
#pragma once
#include <cmath>
#include <type_traits>

namespace phys
{

    template<typename T>
    struct Vec2 {
        T x{}, y{};

        [[nodiscard]] auto length() const {
            using R = std::conditional_t<std::is_integral_v<T>, double, T>;
            return static_cast<R>(std::hypot(static_cast<double>(x),
                                             static_cast<double>(y)));
        }
    };

    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;

}

#endif //SANDBOX2D_VEC2_H