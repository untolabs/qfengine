#ifndef CORE_VECTOR3F_HH
#define CORE_VECTOR3F_HH 1
#pragma once

#include "core/vector3base.hh"

/**
 * A Vector3base extension for floating point type
 */
class Vector3f final : public Vector3base<float> {
public:
    template<typename T>
    constexpr Vector3f(const Vector3base<T> &other);
    constexpr Vector3f(void) : Vector3base<float>() {}
    using Vector3base<float>::Vector3base;

public:
    /**
     * Calculates a vector's cross product
     * @param u The first vector parameter
     * @param v The second vector parameter
     * @returns The cross product of `u` and `v`
     * @see Wikipedia page for [Cross product](https://en.wikipedia.org/wiki/Cross_product)
     */
    constexpr static Vector3f cross(const Vector3f &u, const Vector3f &v);

    /**
     * Calculates a vector's dot product
     * @param u The first vector parameter
     * @param v The second vector parameter
     * @returns The dot product of `u` and `v`
     * @see Wikipedia page for [Dot product](https://en.wikipedia.org/wiki/Dot_product)
     */
    constexpr static float dot(const Vector3f &u, const Vector3f &v);

public:
    /**
     * Calculates a vector's magnitude
     * @param vector The input vector
     * @returns The vector's magnitude
     * @note This is equivalent to `std::sqrt(Vector3f::dot(vector, vector))`
     */
    static float length(const Vector3f &vector);

    /**
     * Calculates a squared vector's magnitude
     * @param vector The input vector
     * @returns The vector's magnitude squared
     * @note This function might be useful in case of comparing two vectors
     * purely by their magnitudes because it doesn't use `std::sqrt` internally
     * @note This is equivalent to `Vector3f::dot(vector, vector)`
     */
    static float length2(const Vector3f &vector);

    /**
     * Creates a normalized vector out of `vector`
     * @param vector The input vector
     * @returns A normalized vector
     * @warning This function does **zero** argument checks
     * against `vector` and will happily put infinity
     * values into a normalized vector of zero length
     */
    static Vector3f normalized(const Vector3f &vector);

    /**
     * Normalizes a vector in-situ
     * @param[in,out] vector The vector to normalize
     * @returns The old vector length
     * @note This replicates the behaviour of `VectorNormalize` function
     * that is present in most of Quake Engine family of game engines
     * @see VDC page for [Vectors](https://developer.valvesoftware.com/wiki/Vector)
     */
    static float normalize(Vector3f &vector);
};

static_assert(sizeof(Vector3f) == sizeof(float[3]));

template<typename T>
constexpr inline Vector3f::Vector3f(const Vector3base<T> &other)
{
    x = static_cast<float>(other.x);
    y = static_cast<float>(other.y);
    z = static_cast<float>(other.z);
}

constexpr inline Vector3f Vector3f::cross(const Vector3f &u, const Vector3f &v)
{
    Vector3f result;
    result.x = u.y * v.z - u.z * v.y;
    result.y = u.z * v.x - u.x * v.z;
    result.z = u.x * v.y - u.y * v.x;
    return result;
}

constexpr inline float Vector3f::dot(const Vector3f &u, const Vector3f &v)
{
    return (u.x * v.x) + (u.y * v.y) + (u.z * v.z);
}

#endif /* CORE_VECTOR3F_HH */
