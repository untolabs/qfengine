#ifndef CORE_CONSTEXPR_HH
#define CORE_CONSTEXPR_HH 1
#pragma once

namespace cxpr
{
/**
 * Figure out an absolute value of `x`
 * @param x The input value
 * @returns Absolute value of `x`
 */
template<typename T>
constexpr static inline const T abs(const T x);

/**
 * Figure out an array's length using C++ template magic
 * @tparam L Fixed-length array's size
 * @returns Value of `L`
 * @note This only works for C-styled arrays that are declared and
 * their size is known at compile-time; this is a syntax sugar function
 * used in cases where usage of `sizeof` is not very pleasant
 */
template<typename T, std::size_t L>
constexpr static inline const std::size_t array_size(const T(&)[L]);

/**
 * Rounds a number up
 * @param x The input value
 * @returns `x` rounded _up_ to the nearest integer
 * @note `T` must be an integer type
 */
template<typename T, typename F>
constexpr static inline const T ceil(const F x);

/**
 * Converts an angle to degrees
 * @param x The input angle
 * @returns `x` in degrees
 */
template<typename T>
constexpr static inline const T degrees(const T x);

/**
 * Rounds a number down
 * @param x The input value
 * @returns `x` rounded _down_ to the nearest integer
 * @note `T` must be an integer type
 */
template<typename T, typename F>
constexpr static inline const T floor(const F x);

/**
 * Clips a number inside a fixed range
 * @param x The input value
 * @param min Minimum possible value
 * @param max Maximum possible value
 */
template<typename T>
constexpr static inline const T clamp(const T x, const T min, const T max);

/**
 * Interpolate between two values
 * @param x The lower value
 * @param y The higher value
 * @param a Interpolation alpha
 * @see Wikipedia page for [Linear Interpolation](https://en.wikipedia.org/wiki/Linear_interpolation)
 * @warning This function does **zero** range checks against `a`
 * so inputting anything outside of 0..1 range produces janky results
 */
template<typename T, typename F>
constexpr static inline const T lerp(const T x, const T y, const F a);

/**
 * Figure out how many bits a number takes
 * @param x The input value
 * @returns Base-2 log of `x`
 */
template<typename T>
constexpr static inline const T log2(const T x);

/**
 * Figure out the greater number of the inputs
 * @param x The input value
 * @param y The input value
 */
template<typename T>
constexpr static inline const T max(const T x, const T y);

/**
 * Figure out the lesser number of the inputs
 * @param x The input value
 * @param y The input value
 */
template<typename T>
constexpr static inline const T min(const T x, const T y);

/**
 * Force an implementation-defined behaviour into being implementation-agnostic
 * @param x The input value
 * @param m The modulo divisor (module?)
 * @returns Mathematically-correct evaluation of `static_cast<T>(x % m)`
 * @note As per both ISO C and ISO C++ standards, sign of the modulo is very much
 * implementation-defined and can be either retained or dropped. When we tried building
 * and running Voxelius for 32-bit x86, the entire game just exploded because modulo on
 * 32-bit retained its sign and produced mathematically-incorrect results that were used
 * as array indices; as one can imagine, using negative array indices isn't a good idea.
 */
template<typename T>
constexpr static inline const T mod_signed(const T x, const T m);

/**
 * Figure out a power of two closest to the number
 * @param x The input value
 * @note This is equivalent to `1 << cxpr::log2(x)`
 */
template<typename T>
constexpr static inline const T pow2(const T x);

/**
 * Converts an angle to radians
 * @param x The input angle
 * @returns `x` in radians
 */
template<typename T>
constexpr static inline const T radians(const T x);

/**
 * Checks if a number is within a set range
 * @param x The input value
 * @param min The lower range threshold
 * @param max The higher range threshold
 * @returns true if `x >= min` and `x <= max`
 */
template<typename T>
constexpr static inline const bool range(const T x, const T min, const T max);

/**
 * Figure out a number's sign
 * @param x The input value
 * @returns
 *  - `T(-1)` if `x` is negative
 *  - `T(+1)` 1 if `x` is positive
 *  - `T(0)` if `x` is zero
 */
template<typename T, typename F>
constexpr static inline const T sign(const F x);

/**
 * Interpolate between two values
 * @param x The lower value
 * @param y The higher value
 * @param a Interpolation alpha
 * @see Wikipedia page for [Smoothstep](https://en.wikipedia.org/wiki/Smoothstep)
 * @note `F` must be a floating-point type
 */
template<typename T, typename F>
constexpr static inline const T smoothstep(const T x, const T y, const F a);
} // namespace cxpr

template<typename T>
constexpr static inline const T cxpr::abs(const T x)
{
    if(x < static_cast<T>(0))
        return -x;
    return x;
}

template<typename T, std::size_t L>
constexpr static inline const std::size_t cxpr::array_size(const T(&)[L])
{
    return L;
}

template<typename T, typename F>
constexpr static inline const T cxpr::ceil(const F x)
{
    static_assert(std::is_integral_v<T>);
    static_assert(std::is_floating_point_v<F>);

    const T ival = static_cast<T>(x);
    if(ival < x)
        return ival + static_cast<T>(1);
    return ival;
}

template<typename T>
constexpr static inline const T cxpr::degrees(const T x)
{
    return x * static_cast<T>(180.0) / static_cast<T>(M_PI);
}

template<typename T, typename F>
constexpr static inline const T cxpr::floor(const F x)
{
    static_assert(std::is_integral_v<T>);
    static_assert(std::is_floating_point_v<F>);

    const T ival = static_cast<T>(x);
    if(ival > x)
        return ival - static_cast<T>(1);
    return ival;
}

template<typename T>
constexpr static inline const T cxpr::clamp(const T x, const T min, const T max)
{
    if(x < min)
        return min;
    if(x > max)
        return max;
    return x;
}

template<typename T, typename F>
constexpr static inline const T cxpr::lerp(const T x, const T y, const F a)
{
    static_assert(std::is_arithmetic_v<T>);
    static_assert(std::is_floating_point_v<F>);
    return static_cast<T>(static_cast<F>(x) * (static_cast<F>(1.0f) - a) + static_cast<F>(y) * a);
}

template<typename T>
constexpr static inline const T cxpr::log2(const T x)
{
    if(x < 2)
        return 0;
    return cxpr::log2<T>((x + 1) >> 1) + 1;
}

template<typename T>
constexpr static inline const T cxpr::max(const T x, const T y)
{
    if(x < y)
        return y;
    return x;
}

template<typename T>
constexpr static inline const T cxpr::min(const T x, const T y)
{
    if(x > y)
        return y;
    return x;
}

template<typename T>
constexpr static inline const T cxpr::mod_signed(const T x, const T m)
{
    static_assert(std::is_signed_v<T>);
    static_assert(std::is_integral_v<T>);
    const T result = static_cast<T>(x % m);
    if(result < T(0))
        return result + m;
    return result;
}

template<typename T>
constexpr static inline const T cxpr::pow2(const T x)
{
    T value = static_cast<T>(1);
    while(value < x)
        value *= static_cast<T>(2);
    return value;
}

template<typename T>
constexpr static inline const T cxpr::radians(const T x)
{
    return x * static_cast<T>(M_PI) / static_cast<T>(180.0);
}

template<typename T>
constexpr static inline const bool cxpr::range(const T x, const T min, const T max)
{
    return ((x >= min) && (x <= max));
}

template<typename T, typename F>
constexpr static inline const T cxpr::sign(const F x)
{
    if(x < F(0))
        return T(-1);
    if(x > F(0))
        return T(+1);
    return T(0);
}

template<typename T, typename F>
constexpr static inline const T cxpr::smoothstep(const T x, const T y, const F a)
{
    static_assert(std::is_arithmetic_v<T>);
    static_assert(std::is_floating_point_v<F>);

    const F t = cxpr::clamp<F>((a - x) / (y - x), F(0), F(1));
    return static_cast<T>(t * t * (F(3) - F(2) * t));
}

#endif /* CORE_CONSTEXPR_HH */
