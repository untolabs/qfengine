#ifndef CORE_VECTOR3BASE_HH
#define CORE_VECTOR3BASE_HH 1
#pragma once

/**
 * A basic templated 3-dimensional vector
 * @note `T` must be an arithmetic type
 */
template<typename T>
class Vector3base {
    static_assert(std::is_arithmetic_v<T>);

public:
    T x;
    T y;
    T z;

public:
    /**
     * Initializes the vector with zeroes
     * @note This is equivalent to `Vector3base::zero`
     */
    constexpr Vector3base(void);

    /**
     * Initialies all the vector's fields with a single filler
     * @param filler The input value
     */
    constexpr Vector3base(T filler);

    /**
     * Initialzes the vector's fields with their
     * respective values from the parameters
     * @param vx X component value
     * @param vy Y component value
     * @param vz Z component value
     */
    constexpr Vector3base(T vx, T vy, T vz);

    /**
     * Initializes the vector with a C-styled buffer
     * @param buffer The input buffer
     * @warning This constructor does **zero** range checks
     * against `buffer` and will happily read past it if provided
     * with a buffer of insufficient capacity
     */
    constexpr Vector3base(const T *buffer);

public:
    constexpr Vector3base<T> operator+(const Vector3base<T> &vector) const;
    constexpr Vector3base<T> operator-(const Vector3base<T> &vector) const;
    constexpr Vector3base<T> operator+(const T scalar) const;
    constexpr Vector3base<T> operator-(const T scalar) const;
    constexpr Vector3base<T> operator*(const T scalar) const;
    constexpr Vector3base<T> operator/(const T scalar) const;

public:
    constexpr Vector3base<T> &operator+=(const Vector3base<T> &vector);
    constexpr Vector3base<T> &operator-=(const Vector3base<T> &vector);
    constexpr Vector3base<T> &operator+=(const T scalar);
    constexpr Vector3base<T> &operator-=(const T scalar);
    constexpr Vector3base<T> &operator*=(const T scalar);
    constexpr Vector3base<T> &operator/=(const T scalar);

public:
    /**
     * @returns Forward-facing unit vector
     */
    constexpr static Vector3base<T> dir_forward(void);

    /**
     * @returns Backwards-facing unit vector
     */
    constexpr static Vector3base<T> dir_back(void);

    /**
     * @returns Left-facing unit vector
     */
    constexpr static Vector3base<T> dir_left(void);

    /**
     * @returns Right-facing unit vector
     */
    constexpr static Vector3base<T> dir_right(void);

    /**
     * @returns Down-facing unit vector
     */
    constexpr static Vector3base<T> dir_down(void);

    /**
     * @returns Up-facing unit vector
     */
    constexpr static Vector3base<T> dir_up(void);

public:
    /**
     * Creates a vector with zero fields
     * @returns A vector with its fields initialized to zero
     */
    constexpr static Vector3base<T> zero(void);

    /**
     * Creates a vector with all zero fields except one
     * @param d Dimension
     * @param value The value
     * @returns A vector with all fields set to zero except `d`th field set to `value`
     * @warning This function does **zero** range checks
     * against `d` and will happily write past the vector if
     * given an argument out of allowed range of 0..2
     */
    constexpr static Vector3base<T> zero_except(unsigned int d, const T value);
};

template<typename T>
constexpr inline Vector3base<T>::Vector3base(void)
{
    x = 0;
    y = 0;
    z = 0;
}

template<typename T>
constexpr inline Vector3base<T>::Vector3base(T filler)
{
    x = filler;
    y = filler;
    z = filler;
}

template<typename T>
constexpr inline Vector3base<T>::Vector3base(T vx, T vy, T vz)
{
    x = vx;
    y = vy;
    z = vz;
}

template<typename T>
constexpr inline Vector3base<T>::Vector3base(const T *buffer)
{
    x = buffer[0];
    y = buffer[1];
    z = buffer[2];
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::operator+(const Vector3base<T> &vector) const
{
    return Vector3base<T>((x + vector.x), (y + vector.y), (z + vector.z));
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::operator-(const Vector3base<T> &vector) const
{
    return Vector3base<T>((x - vector.x), (y - vector.y), (z - vector.z));
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::operator+(const T scalar) const
{
    return Vector3base<T>((x + scalar), (y + scalar), (z + scalar));
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::operator-(const T scalar) const
{
    return Vector3base<T>((x - scalar), (y - scalar), (z - scalar));
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::operator*(const T scalar) const
{
    return Vector3base<T>((x * scalar), (y * scalar), (z * scalar));
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::operator/(const T scalar) const
{
    return Vector3base<T>((x / scalar), (y / scalar), (z / scalar));
}

template<typename T>
constexpr inline Vector3base<T> &Vector3base<T>::operator+=(const Vector3base<T> &vector)
{
    x += vector.x;
    y += vector.y;
    z += vector.z;
    return *this;
}

template<typename T>
constexpr inline Vector3base<T> &Vector3base<T>::operator-=(const Vector3base<T> &vector)
{
    x -= vector.x;
    y -= vector.y;
    z -= vector.z;
    return *this;
}

template<typename T>
constexpr inline Vector3base<T> &Vector3base<T>::operator+=(const T scalar)
{
    x += scalar;
    y += scalar;
    z += scalar;
    return *this;
}

template<typename T>
constexpr inline Vector3base<T> &Vector3base<T>::operator-=(const T scalar)
{
    x -= scalar;
    y -= scalar;
    z -= scalar;
    return *this;
}

template<typename T>
constexpr inline Vector3base<T> &Vector3base<T>::operator*=(const T scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}

template<typename T>
constexpr inline Vector3base<T> &Vector3base<T>::operator/=(const T scalar)
{
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::dir_forward(void)
{
    return Vector3base<T>(0, 0, T(+1));
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::dir_back(void)
{
    return Vector3base<T>(0, 0, T(-1));
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::dir_left(void)
{
    return Vector3base<T>(T(-1), 0, 0);
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::dir_right(void)
{
    return Vector3base<T>(T(+1), 0, 0);
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::dir_down(void)
{
    return Vector3base<T>(0, T(-1), 0);
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::dir_up(void)
{
    return Vector3base<T>(0, T(+1), 0);
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::zero(void)
{
    return Vector3base<T>(0, 0, 0);
}

template<typename T>
constexpr inline Vector3base<T> Vector3base<T>::zero_except(unsigned int d, const T value)
{
    Vector3base<T> result = Vector3base<T>::zero();
    reinterpret_cast<float *>(&result)[d] = value;
    return result;
}

#endif /* CORE_VECTOR3BASE_HH */
