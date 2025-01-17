#ifndef CORE_MATRIX4X4F_HH
#define CORE_MATRIX4X4F_HH 1
#pragma once

#include "core/matrix4x4base.hh"
#include "core/vector3angles.hh"

/**
 * A Matrix4base extension for floating point type
 */
class Matrix4x4f final : public Matrix4x4base<float> {
public:
    template<typename T>
    constexpr Matrix4x4f(const Matrix4x4base<T> &other);
    constexpr Matrix4x4f(void) : Matrix4x4base<float>() {}
    using Matrix4x4base<float>::Matrix4x4base;

public:
    /**
     * Applies rotation to an existing model matrix
     * @param model Input model matrix
     * @param angle Rotation angle, in radians
     * @param axis Rotation axis
     * @returns `model` rotated by `angle` around `axis`
     */
    static Matrix4x4f model_rotate(const Matrix4x4f &model, float angle, const Vector3f &axis);

    /**
     * Creates an orthographic projection matrix
     * @param left Left-most edge of the view area
     * @param right Right-most edge of the view area
     * @param bottom Bottom-most edge of the view area
     * @param top Top-most edge of the view area
     * @param z_near Near clipping plane distance
     * @param z_far Far clipping plane distance
     * @see Wikipedia page for [Orthographic projection](https://en.wikipedia.org/wiki/Orthographic_projection)
     */
    static Matrix4x4f proj_ortho(float left, float right, float bottom, float top, float z_near, float z_far);

    /**
     * Creates a perspective projection matrix
     * @param y_fov Vertical field of view, in radians
     * @param aspect Screen aspect ratio
     * @param z_near Near clipping plane distance
     * @param z_far Far clipping plane distance
     * @see Wikipedia page for [Perspective projection](https://en.wikipedia.org/wiki/Perspective_(graphical))
     */
    static Matrix4x4f proj_persp(float y_fov, float aspect, float z_near, float z_far);

    /**
     * Creates a view (camera) matrix from position and Euler angles
     * @param position Camera position
     * @param angles Camera view angles
     * @returns A view matrix that allows pitch angles of any range
     * @note This specific matrix is also used in [PlatinumSrc](https://github.com/PlatinumSrc/PlatinumSrc)
     * and in fact has been directly contributed to Voxelius (and by extension QFengine) by
     * [PQCraft](https://github.com/PQCraft) himeself
     */
    static Matrix4x4f view_psrc(const Vector3f &position, const Vector3angles &angles);
};

static_assert(sizeof(Matrix4x4f) == sizeof(float[4][4]));

template<typename T>
constexpr inline Matrix4x4f::Matrix4x4f(const Matrix4x4base<T> &other)
{
    D0 = Vector4base<float>(other.D0);
    D1 = Vector4base<float>(other.D1);
    D2 = Vector4base<float>(other.D2);
    D3 = Vector4base<float>(other.D3);
}

#endif /* CORE_MATRIX4X4F_HH */
