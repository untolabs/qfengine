#ifndef CORE_VECTOR2F_HH
#define CORE_VECTOR2F_HH 1
#pragma once

#include "core/vector2base.hh"

/**
 * A Vector2base extension for floating point type
 */
class Vector2f final : public Vector2base<float> {
public:
    template<typename T>
    constexpr Vector2f(const Vector2base<T> &other);
    constexpr Vector2f(void) : Vector2base<float>() {}
    using Vector2base<float>::Vector2base;

public:
    /**
     * Calculates a vector's dot product
     * @param u The first vector parameter
     * @param v The second vector parameter
     * @returns The dot product of `u` and `v`
     * @see Wikipedia page for [Dot product](https://en.wikipedia.org/wiki/Dot_product)
     */
    constexpr static float dot(const Vector2f &u, const Vector2f &v);

public:
    /**
     * Calculates a vector's magnitude
     * @param vector The input vector
     * @returns The vector's magnitude
     * @note This is equivalent to `std::sqrt(Vector2f::dot(vector, vector))`
     */
    static float length(const Vector2f &vector);

    /**
     * Calculates a squared vector's magnitude
     * @param vector The input vector
     * @returns The vector's magnitude squared
     * @note This function might be useful in case of comparing two vectors
     * purely by their magnitudes because it doesn't use `std::sqrt` internally
     * @note This is equivalent to `Vector2f::dot(vector, vector)`
     */
    static float length2(const Vector2f &vector);

    /**
     * Creates a normalized vector out of `vector`
     * @param vector The input vector
     * @returns A normalized vector
     * @warning This function does **zero** argument checks
     * against `vector` and will happily put infinity
     * values into a normalized vector of zero length
     */
    static Vector2f normalized(const Vector2f &vector);

    /**
     * Normalizes a vector in-situ
     * @param[in,out] vector The vector to normalize
     * @returns The old vector length
     * @note This replicates the behaviour of `VectorNormalize` function
     * that is present in most of Quake Engine family of game engines
     * @see VDC page for [Vectors](https://developer.valvesoftware.com/wiki/Vector)
     */
    static float normalize(Vector2f &vector);
};

static_assert(sizeof(Vector2f) == sizeof(float[2]));

template<typename T>
constexpr inline Vector2f::Vector2f(const Vector2base<T> &other)
{
    x = static_cast<float>(other.x);
    y = static_cast<float>(other.y);
}

constexpr inline float Vector2f::dot(const Vector2f &u, const Vector2f &v)
{
    return (u.x * v.x) + (u.y * v.y);
}

#endif /* CORE_VECTOR2F_HH */
