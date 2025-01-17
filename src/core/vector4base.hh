#ifndef CORE_VECTOR4BASE_HH
#define CORE_VECTOR4BASE_HH 1
#pragma once

/**
 * A basic templated 4-dimensional vector
 * @note `T` must be an arithmetic type
 */
template<typename T>
class Vector4base {
    static_assert(std::is_arithmetic_v<T>);

public:
    T x;
    T y;
    T z;
    T w;

public:
    /**
     * Initializes the vector with zeroes
     */
    constexpr Vector4base(void);

    /**
     * Initialies all the vector's fields with a single filler
     * @param filler The input value
     */
    constexpr Vector4base(T filler);

    /**
     * Initialzes the vector's fields with their
     * respective values from the parameters
     * @param vx X component value
     * @param vy Y component value
     * @param vz Z component value
     * @param vw W component value
     */
    constexpr Vector4base(T vx, T vy, T vz, T vw);

    /**
     * Initializes the vector with a C-styled buffer
     * @param buffer The input buffer
     * @warning This constructor does **zero** range checks
     * against `buffer` and will happily read past it if provided
     * with a buffer of insufficient capacity
     */
    constexpr Vector4base(const T *buffer);

public:
    constexpr Vector4base<T> operator+(const Vector4base<T> &vector) const;
    constexpr Vector4base<T> operator-(const Vector4base<T> &vector) const;
    constexpr Vector4base<T> operator+(const T scalar) const;
    constexpr Vector4base<T> operator-(const T scalar) const;
    constexpr Vector4base<T> operator*(const T scalar) const;
    constexpr Vector4base<T> operator/(const T scalar) const;

public:
    constexpr Vector4base<T> &operator+=(const Vector4base<T> &vector);
    constexpr Vector4base<T> &operator-=(const Vector4base<T> &vector);
    constexpr Vector4base<T> &operator+=(const T scalar);
    constexpr Vector4base<T> &operator-=(const T scalar);
    constexpr Vector4base<T> &operator*=(const T scalar);
    constexpr Vector4base<T> &operator/=(const T scalar);
};

template<typename T>
constexpr inline Vector4base<T>::Vector4base(void)
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}

template<typename T>
constexpr inline Vector4base<T>::Vector4base(T filler)
{
    x = filler;
    y = filler;
    z = filler;
    w = filler;
}

template<typename T>
constexpr inline Vector4base<T>::Vector4base(T vx, T vy, T vz, T vw)
{
    x = vx;
    y = vy;
    z = vz;
    w = vw;
}

template<typename T>
constexpr inline Vector4base<T>::Vector4base(const T *buffer)
{
    x = buffer[0];
    y = buffer[1];
    z = buffer[2];
    w = buffer[3];
}

template<typename T>
constexpr inline Vector4base<T> Vector4base<T>::operator+(const Vector4base<T> &vector) const
{
    return Vector4base<T>((x + vector.x), (y + vector.y), (z + vector.z), (w + vector.w));
}

template<typename T>
constexpr inline Vector4base<T> Vector4base<T>::operator-(const Vector4base<T> &vector) const
{
    return Vector4base<T>((x - vector.x), (y - vector.y), (z - vector.z), (w - vector.w));
}

template<typename T>
constexpr inline Vector4base<T> Vector4base<T>::operator+(const T scalar) const
{
    return Vector4base<T>((x + scalar), (y + scalar), (z + scalar), (w + scalar));
}

template<typename T>
constexpr inline Vector4base<T> Vector4base<T>::operator-(const T scalar) const
{
    return Vector4base<T>((x - scalar), (y - scalar), (z - scalar), (w - scalar));
}

template<typename T>
constexpr inline Vector4base<T> Vector4base<T>::operator*(const T scalar) const
{
    return Vector4base<T>((x * scalar), (y * scalar), (z * scalar), (w * scalar));
}

template<typename T>
constexpr inline Vector4base<T> Vector4base<T>::operator/(const T scalar) const
{
    return Vector4base<T>((x / scalar), (y / scalar), (z / scalar), (w / scalar));
}

template<typename T>
constexpr inline Vector4base<T> &Vector4base<T>::operator+=(const Vector4base<T> &vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    w += vector.w;
    return *this;
}

template<typename T>
constexpr inline Vector4base<T> &Vector4base<T>::operator-=(const Vector4base<T> &vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    w -= vector.w;
    return *this;
}

template<typename T>
constexpr inline Vector4base<T> &Vector4base<T>::operator+=(const T scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;
    w += scalar;
    return *this;
}

template<typename T>
constexpr inline Vector4base<T> &Vector4base<T>::operator-=(const T scalar)
{
    x -= scalar;
    y -= scalar;
    z -= scalar;
    w -= scalar;
    return *this;
}

template<typename T>
constexpr inline Vector4base<T> &Vector4base<T>::operator*=(const T scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;
    return *this;
}

template<typename T>
constexpr inline Vector4base<T> &Vector4base<T>::operator/=(const T scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    w /= scalar;
    return *this;
}

#endif /* CORE_VECTOR4BASE_HH */
