//
// Created by Jacopo Uggeri on 16/08/2025.
//
#pragma once
#include <cmath>
#include <type_traits>

namespace phys
{

    template<typename T>
    struct Vec2 {
        T x{}, y{};

        [[nodiscard]] constexpr auto length() const {
            using R = std::conditional_t<std::is_integral_v<T>, double, T>;
            return static_cast<R>(std::hypot(static_cast<double>(x),
                                             static_cast<double>(y)));
        }

        [[nodiscard]] constexpr auto dot(const Vec2& other) const {
            using R = std::conditional_t<std::is_integral_v<T>, double, T>;
            return static_cast<R>(static_cast<double>(x) * static_cast<double>(other.x) +
                                  static_cast<double>(y) * static_cast<double>(other.y));
        }

        constexpr Vec2 tensorDot(const Vec2& other) {
            return {x * other.x, y * other.y};
        }

        constexpr Vec2 operator+(const Vec2& other) const {
            return {x + other.x, y + other.y};
        }

        constexpr Vec2 operator-(const Vec2& other) const {
            return {x - other.x, y - other.y};
        }

        constexpr Vec2& operator+=(const Vec2& other) {
            x += other.x;
            y += other.y;
            return *this;
        }

        constexpr Vec2& operator-=(const Vec2& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }

        constexpr Vec2 operator*(T scalar) const {
            return {x * scalar, y * scalar};
        }

        constexpr Vec2 operator/(T scalar) const {
            return {x / scalar, y / scalar};
        }

        // Allow cast conversion
        template<typename U>
        constexpr explicit operator Vec2<U>() const {
            return {static_cast<U>(x), static_cast<U>(y)};
        }
    };

    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;

}