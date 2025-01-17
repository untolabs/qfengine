#ifndef CORE_VECTOR4F_HH
#define CORE_VECTOR4F_HH 1
#pragma once

#include "core/vector4base.hh"

/**
 * A Vector4base extension for floating point type
 */
class Vector4f final : public Vector4base<float> {
public:
    template<typename T>
    constexpr Vector4f(const Vector4base<T> &other);
    constexpr Vector4f(void) : Vector4base<float>() {}
    using Vector4base<float>::Vector4base;

public:
    /**
     * Returns a vector containing normalized RGBA for black color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f black(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for black color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f blue(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for brown color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f brown(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for cyan color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f cyan(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for dark blue color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f dark_blue(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for dark cyan color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f dark_cyan(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for dark green color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f dark_green(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for dark magenta color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f dark_magenta(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for dark red color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f dark_red(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for gray color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f gray(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for green color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f green(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for light blue color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f light_blue(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for light gray color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f light_gray(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for magenta color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f magenta(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for red color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f red(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for white color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f white(const float alpha = 1.00f);

    /**
     * Returns a vector containing normalized RGBA for yellow color
     * @param alpha Alpha component of the color
     */
    constexpr static Vector4f yellow(const float alpha = 1.00f);

public:
    /**
     * Returns a vector containing normalized RGBA for black transparent color
     * @note This is equivalent to `Vector4f::black(0.00f)`
     */
    constexpr static Vector4f transparent(void);
};

static_assert(sizeof(Vector4f) == sizeof(float[4]));

template<typename T>
constexpr inline Vector4f::Vector4f(const Vector4base<T> &other)
{
    x = static_cast<float>(other.x);
    y = static_cast<float>(other.y);
    z = static_cast<float>(other.z);
    z = static_cast<float>(other.w);
}

constexpr inline Vector4f Vector4f::black(const float alpha)
{
    return Vector4f(0.00f, 0.00f, 0.00f, alpha);
}

constexpr inline Vector4f Vector4f::blue(const float alpha)
{
    return Vector4f(0.00f, 0.00f, 1.00f, alpha);
}

constexpr inline Vector4f Vector4f::brown(const float alpha)
{
    return Vector4f(0.50f, 0.50f, 0.00f, alpha);
}

constexpr inline Vector4f Vector4f::cyan(const float alpha)
{
    return Vector4f(0.00f, 1.00f, 1.00f, alpha);
}

constexpr inline Vector4f Vector4f::dark_blue(const float alpha)
{
    return Vector4f(0.00f, 0.00f, 0.50f, alpha);
}

constexpr inline Vector4f Vector4f::dark_cyan(const float alpha)
{
    return Vector4f(0.00f, 0.50f, 0.50f, alpha);
}

constexpr inline Vector4f Vector4f::dark_green(const float alpha)
{
    return Vector4f(0.00f, 0.50f, 0.00f, alpha);
}

constexpr inline Vector4f Vector4f::dark_magenta(const float alpha)
{
    return Vector4f(0.50f, 0.00f, 0.50f, alpha);
}

constexpr inline Vector4f Vector4f::dark_red(const float alpha)
{
    return Vector4f(0.50f, 0.00f, 0.00f, alpha);
}

constexpr inline Vector4f Vector4f::gray(const float alpha)
{
    return Vector4f(0.50f, 0.50f, 0.50f, alpha);
}

constexpr inline Vector4f Vector4f::green(const float alpha)
{
    return Vector4f(0.00f, 1.00f, 0.00f, alpha);
}

constexpr inline Vector4f Vector4f::light_blue(const float alpha)
{
    return Vector4f(0.68f, 0.85f, 0.90f, alpha);
}

constexpr inline Vector4f Vector4f::light_gray(const float alpha)
{
    return Vector4f(0.80f, 0.80f, 0.80f, alpha);
}

constexpr inline Vector4f Vector4f::magenta(const float alpha)
{
    return Vector4f(1.00f, 0.00f, 1.00f, alpha);
}

constexpr inline Vector4f Vector4f::red(const float alpha)
{
    return Vector4f(1.00f, 0.00f, 0.00f, alpha);
}

constexpr inline Vector4f Vector4f::white(const float alpha)
{
    return Vector4f(1.00f, 1.00f, 1.00f, alpha);
}

constexpr inline Vector4f Vector4f::yellow(const float alpha)
{
    return Vector4f(1.00f, 1.00f, 0.00f, alpha);
}

constexpr inline Vector4f Vector4f::transparent(void)
{
    return Vector4f(0.00f, 0.00f, 0.00f, 0.00f);
}

#endif /* CORE_VECTOR4F_HH */
