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

        [[nodiscard]] constexpr auto normalized() const {
            using R = std::conditional_t<std::is_integral_v<T>, double, T>;
            const auto len = length();
            if (len == 0) return Vec2{};
            return Vec2{static_cast<R>(x) / len, static_cast<R>(y) / len};
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

    template<typename T>
    constexpr Vec2<T> operator*(T scalar, const Vec2<T>& vec) {
        return {vec.x * scalar, vec.y * scalar};
    }

    template<typename T>
    constexpr Vec2<T> lerp(const Vec2<T>& a, const Vec2<T>& b, double t) {
        return a + (b - a) * t;
    }

    using Vec2i = Vec2<int>;
    using Vec2f = Vec2<float>;

}