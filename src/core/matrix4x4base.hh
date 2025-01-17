#ifndef CORE_MATRIX4X4BASE_HH
#define CORE_MATRIX4X4BASE_HH 1
#pragma once

#include "core/vector3base.hh"
#include "core/vector4base.hh"

/**
 * A basic templated 4x4 matrix
 * @note `T` must be an arithmetic type
 */
template<typename T>
class Matrix4x4base {
    static_assert(std::is_arithmetic_v<T>);

public:
    Vector4base<T> D0;
    Vector4base<T> D1;
    Vector4base<T> D2;
    Vector4base<T> D3;

public:
    /**
     * Initializes the matrix with implementation-defined data
     * @warning Contents of row fields are implementation-defined
     */
    constexpr Matrix4x4base(void) = default;

    /**
     * Initializes the matrix with 4-dimensional vectors as its rows
     * @param vD0 1st row of the matrix
     * @param vD1 2nd row of the matrix
     * @param vD2 3rd row of the matrix
     * @param vD3 4th row of the matrix
     */
    constexpr Matrix4x4base(const Vector4base<T> &vD0, const Vector4base<T> &vD1, const Vector4base<T> &vD2, const Vector4base<T> &vD3);

    /**
     * Initializes the matrix with a C-styled buffer
     * @param buffer The input buffer
     * @warning This constructor does **zero** range checks
     * against `buffer` and will happily read past it if provided
     * with a buffer of insufficient capacity
     */
    constexpr Matrix4x4base(const T *buffer);

public:
    /**
     * Calculates the product of a 4x4 matrix and a 3-dimensional vector
     * @param matrix The 4x4 matrix
     * @param vector The 3-dimensional vector
     * @note The vector is padded with the W component value of 1.0:  
     * 
     * $$M=\begin{pmatrix}A_{11}&A_{12}&A_{13}&A_{14}\\A_{21}&A_{22}&A_{23}&A_{24}
     * \\A_{31}&A_{32}&A_{33}&A_{34}\\A_{41}&A_{42}&A_{43}&A_{44}\\\end{pmatrix}\cdot
     * \begin{pmatrix}V_{1}\\V_{2}\\V_{3}\\1.0\\\end{pmatrix}$$
     */
    constexpr static Vector4base<T> product(const Matrix4x4base<T> &matrix, const Vector3base<T> &vector);

    /**
     * Calculates the product of a 4x4 matrix and a 4-dimensional vector
     * @param matrix The 4x4 matrix
     * @param vector The 4-dimensional vector
     * @note Most of the time, the vector's W component should be 1.0
     */
    constexpr static Vector4base<T> product(const Matrix4x4base<T> &matrix, const Vector4base<T> &vector);

    /**
     * Calculates the product of two 4x4 matrices
     * @param A Left-hand matrix
     * @param B Right-hand matrix
     * @warning Multiplicaton order matters!
     */
    constexpr static Matrix4x4base<T> product(const Matrix4x4base<T> &A, const Matrix4x4base<T> &B);

public:
    /**
     * @see Wikipedia page for [Identity matrix](https://en.wikipedia.org/wiki/Identity_matrix)
     * @returns An identity matrix
     */
    constexpr static Matrix4x4base<T> identity(void);

    /**
     * @returns A matrix filled with zero values
     * @note Most of the time this function is to be used for
     * internal initialization of matrices for specific typed
     * implementations of Matrix4x4base
     */
    constexpr static Matrix4x4base<T> zero(void);
};

template<typename T>
constexpr inline Matrix4x4base<T>::Matrix4x4base(const Vector4base<T> &vD0, const Vector4base<T> &vD1, const Vector4base<T> &vD2, const Vector4base<T> &vD3)
{
    D0 = vD0;
    D1 = vD1;
    D2 = vD2;
    D3 = vD3;
}

template<typename T>
constexpr inline Matrix4x4base<T>::Matrix4x4base(const T *buffer)
{
    D0.x = buffer[0x00];
    D0.y = buffer[0x01];
    D0.z = buffer[0x02];
    D0.w = buffer[0x03];

    D1.x = buffer[0x04];
    D1.y = buffer[0x05];
    D1.z = buffer[0x06];
    D1.w = buffer[0x07];

    D2.x = buffer[0x08];
    D2.y = buffer[0x09];
    D2.z = buffer[0x0A];
    D2.w = buffer[0x0B];

    D3.x = buffer[0x0C];
    D3.y = buffer[0x0D];
    D3.z = buffer[0x0E];
    D3.w = buffer[0x0F];
}

template<typename T>
constexpr inline Vector4base<T> Matrix4x4base<T>::product(const Matrix4x4base<T> &matrix, const Vector3base<T> &vector)
{
    Vector4base<T> result;
    result.x = matrix.D0.x * vector.x + matrix.D1.x * vector.y + matrix.D2.x * vector.z + matrix.D3.x;
    result.y = matrix.D0.y * vector.x + matrix.D1.y * vector.y + matrix.D2.y * vector.z + matrix.D3.y;
    result.z = matrix.D0.z * vector.x + matrix.D1.z * vector.y + matrix.D2.z * vector.z + matrix.D3.z;
    result.w = matrix.D0.w * vector.x + matrix.D1.w * vector.y + matrix.D2.w * vector.z + matrix.D3.w;
    return result;
}

template<typename T>
constexpr inline Vector4base<T> Matrix4x4base<T>::product(const Matrix4x4base<T> &matrix, const Vector4base<T> &vector)
{
    Vector4base<T> result;
    result.x = matrix.D0.x * vector.x + matrix.D1.x * vector.y + matrix.D2.x * vector.z + matrix.D3.x * vector.w;
    result.y = matrix.D0.y * vector.x + matrix.D1.y * vector.y + matrix.D2.y * vector.z + matrix.D3.y * vector.w;
    result.z = matrix.D0.z * vector.x + matrix.D1.z * vector.y + matrix.D2.z * vector.z + matrix.D3.z * vector.w;
    result.w = matrix.D0.w * vector.x + matrix.D1.w * vector.y + matrix.D2.w * vector.z + matrix.D3.w * vector.w;
    return result;
}

template<typename T>
constexpr inline Matrix4x4base<T> Matrix4x4base<T>::product(const Matrix4x4base<T> &A, const Matrix4x4base<T> &B)
{
    Matrix4x4base<T> result;
	result.D0 = A.D0 * B.D0.x + A.D1 * B.D0.y + A.D2 * B.D0.z + A.D3 * B.D0.w;
	result.D1 = A.D0 * B.D1.x + A.D1 * B.D1.y + A.D2 * B.D1.z + A.D3 * B.D1.w;
	result.D2 = A.D0 * B.D2.x + A.D1 * B.D2.y + A.D2 * B.D2.z + A.D3 * B.D2.w;
	result.D3 = A.D0 * B.D3.x + A.D1 * B.D3.y + A.D2 * B.D3.z + A.D3 * B.D3.w;
    return result;
}

template<typename T>
constexpr inline Matrix4x4base<T> Matrix4x4base<T>::identity(void)
{
    Matrix4x4base<T> result;
    result.D0 = Vector4base<T>(1, 0, 0, 0);
    result.D1 = Vector4base<T>(0, 1, 0, 0);
    result.D2 = Vector4base<T>(0, 0, 1, 0);
    result.D3 = Vector4base<T>(0, 0, 0, 1);
    return result;
}

template<typename T>
constexpr inline Matrix4x4base<T> Matrix4x4base<T>::zero(void)
{
    Matrix4x4base<T> result;
    result.D0 = Vector4base<T>(0, 0, 0, 0);
    result.D1 = Vector4base<T>(0, 0, 0, 0);
    result.D2 = Vector4base<T>(0, 0, 0, 0);
    result.D3 = Vector4base<T>(0, 0, 0, 0);
    return result;
}

#endif /* CORE_MATRIX4X4BASE_HH */
