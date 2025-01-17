#ifndef CORE_VECTOR2BASE_HH
#define CORE_VECTOR2BASE_HH 1
#pragma once

/**
 * A basic templated 2-dimensional vector
 * @note `T` must be an arithmetic type
 */
template<typename T>
class Vector2base {
    static_assert(std::is_arithmetic_v<T>);

public:
    T x;
    T y;

public:
    /**
     * Initializes the vector with zeroes
     * @note This is equivalent to `Vector2base::zero`
     */
    constexpr Vector2base(void);

    /**
     * Initialies all the vector's fields with a single filler
     * @param filler The input value
     */
    constexpr Vector2base(T filler);

    /**
     * Initialzes the vector's fields with their
     * respective values from the parameters
     * @param vx X component value
     * @param vy Y component value
     */
    constexpr Vector2base(T vx, T vy);

    /**
     * Initializes the vector with a C-styled buffer
     * @param buffer The input buffer
     * @warning This constructor does **zero** range checks
     * against `buffer` and will happily read past it if provided
     * with a buffer of insufficient capacity
     */
    constexpr Vector2base(const T *buffer);

public:
    constexpr Vector2base<T> operator+(const Vector2base<T> &vector) const;
    constexpr Vector2base<T> operator-(const Vector2base<T> &vector) const;
    constexpr Vector2base<T> operator+(const T scalar) const;
    constexpr Vector2base<T> operator-(const T scalar) const;
    constexpr Vector2base<T> operator*(const T scalar) const;
    constexpr Vector2base<T> operator/(const T scalar) const;

public:
    constexpr Vector2base<T> &operator+=(const Vector2base<T> &vector);
    constexpr Vector2base<T> &operator-=(const Vector2base<T> &vector);
    constexpr Vector2base<T> &operator+=(const T scalar);
    constexpr Vector2base<T> &operator-=(const T scalar);
    constexpr Vector2base<T> &operator*=(const T scalar);
    constexpr Vector2base<T> &operator/=(const T scalar);

public:
    /**
     * Creates a vector with zero fields
     * @returns A vector with its fields initialized to zero
     */
    constexpr Vector2base<T> zero(void);
};

template<typename T>
constexpr inline Vector2base<T>::Vector2base(void)
{
    x = 0;
    y = 0;
}

template<typename T>
constexpr inline Vector2base<T>::Vector2base(T filler)
{
    x = filler;
    y = filler;
}

template<typename T>
constexpr inline Vector2base<T>::Vector2base(T vx, T vy)
{
    x = vx;
    y = vy;
}

template<typename T>
constexpr inline Vector2base<T>::Vector2base(const T *buffer)
{
    x = buffer[0];
    y = buffer[1];
}

template<typename T>
constexpr inline Vector2base<T> Vector2base<T>::operator+(const Vector2base<T> &vector) const
{
    return Vector2base<T>((x + vector.x), (y + vector.y));
}

template<typename T>
constexpr inline Vector2base<T> Vector2base<T>::operator-(const Vector2base<T> &vector) const
{
    return Vector2base<T>((x - vector.x), (y - vector.y));
}

template<typename T>
constexpr inline Vector2base<T> Vector2base<T>::operator+(const T scalar) const
{
    return Vector2base<T>((x + scalar), (y + scalar));
}

template<typename T>
constexpr inline Vector2base<T> Vector2base<T>::operator-(const T scalar) const
{
    return Vector2base<T>((x - scalar), (y - scalar));
}

template<typename T>
constexpr inline Vector2base<T> Vector2base<T>::operator*(const T scalar) const
{
    return Vector2base<T>((x * scalar), (y * scalar));
}

template<typename T>
constexpr inline Vector2base<T> Vector2base<T>::operator/(const T scalar) const
{
    return Vector2base<T>((x / scalar), (y / scalar));
}

template<typename T>
constexpr inline Vector2base<T> &Vector2base<T>::operator+=(const Vector2base<T> &vector)
{
    x += vector.x;
    y += vector.y;
    return *this;
}

template<typename T>
constexpr inline Vector2base<T> &Vector2base<T>::operator-=(const Vector2base<T> &vector)
{
    x -= vector.x;
    y -= vector.y;
    return *this;
}

template<typename T>
constexpr inline Vector2base<T> &Vector2base<T>::operator+=(const T scalar)
{
    x += scalar;
    y += scalar;
    return *this;
}

template<typename T>
constexpr inline Vector2base<T> &Vector2base<T>::operator-=(const T scalar)
{
    x -= scalar;
    y -= scalar;
    return *this;
}

template<typename T>
constexpr inline Vector2base<T> &Vector2base<T>::operator*=(const T scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

template<typename T>
constexpr inline Vector2base<T> &Vector2base<T>::operator/=(const T scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

template<typename T>
constexpr inline Vector2base<T> Vector2base<T>::zero(void)
{
    return Vector2base<T>(0, 0);
}

#endif /* CORE_VECTOR2BASE_HH */
