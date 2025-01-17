#ifndef CORE_VECTOR3ANGLES_HH
#define CORE_VECTOR3ANGLES_HH 1
#pragma once

#include "core/constexpr.hh"
#include "core/vector3f.hh"

/**
 * A Vector3base extension for floating-point Euler angles
 */
class Vector3angles final : public Vector3base<float> {
public:
    template<typename T>
    constexpr Vector3angles(const Vector3base<T> &other);
    constexpr Vector3angles(void) : Vector3base<float>() {}
    using Vector3base<float>::Vector3base;

public:
    /**
     * Converts Euler angles into degrees
     * @param angles Euler angles in radians
     * @returns Euler angles in degrees
     */
    constexpr static Vector3angles degrees(const Vector3angles &angles);

    /**
     * Converts Euler angles into radians
     * @param angles Euler angles in degrees
     * @returns Euler angles in radians
     */
    constexpr static Vector3angles radians(const Vector3angles &angles);

public:
    /**
     * Wraps Euler angles into -180..180 degree range
     * @param angles Input euler angles
     * @returns Wrapped Euler angles
     */
    static Vector3angles wrap_180(const Vector3angles &angles);

    /**
     * Wraps Euler angles into 0..360 degree range
     * @param angles Input euler angles
     * @returns Wrapped Euler angles
     */
    static Vector3angles wrap_360(const Vector3angles &angles);

public:
    /**
     * Calculates cosines of each angle
     * @param angles Input Euler angles in radians
     * @returns A vector with per-component cosine values
     */
    static Vector3f cos(const Vector3angles &angles);

    /**
     * Calculates sines of each angle
     * @param angles Input Euler angles in radians
     * @returns A vector with per-component sine values
     */
    static Vector3f sin(const Vector3angles &angles);

public:
    /**
     * Figures out the forward-facing vector from angles
     * @param angles Input Euler angles
     * @param[out] forward Forward-facing vector
     * @note this replicates the behaviour of `AngleVectors` function
     * that is present in most of Quake Engine family of game engines
     * @see VDC page for [AngleVectors](https://developer.valvesoftware.com/wiki/AngleVectors())
     */
    static void vectors(const Vector3angles &angles, Vector3f &forward);

    /**
     * Figures out three basis vectors from angles
     * @param angles Input Euler angles
     * @param[out] forward Forward-facing vector
     * @param[out] right Right-facing vector
     * @param[out] up Up-facing vector
     * @note If all `forward`, `right` and `up` are `nullptr`, the function does nothing
     * @note this replicates the behaviour of `AngleVectors` function
     * that is present in most of Quake Engine family of game engines
     * @see VDC page for [AngleVectors](https://developer.valvesoftware.com/wiki/AngleVectors())
     */
    static void vectors(const Vector3angles &angles, Vector3f *forward, Vector3f *right, Vector3f *up);
};

static_assert(sizeof(Vector3angles) == sizeof(float[3]));

template<typename T>
constexpr inline Vector3angles::Vector3angles(const Vector3base<T> &other)
{
    x = static_cast<float>(other.x);
    y = static_cast<float>(other.y);
    z = static_cast<float>(other.z);
}

constexpr inline Vector3angles Vector3angles::degrees(const Vector3angles &angles)
{
    Vector3angles result;
    result.x = cxpr::degrees(angles.x);
    result.y = cxpr::degrees(angles.y);
    result.z = cxpr::degrees(angles.z);
    return result;
}

constexpr inline Vector3angles Vector3angles::radians(const Vector3angles &angles)
{
    Vector3angles result;
    result.x = cxpr::radians(angles.x);
    result.y = cxpr::radians(angles.y);
    result.z = cxpr::radians(angles.z);
    return result;
}

#endif /* CORE_VECTOR3ANGLES_HH */
