#include "core/precompiled.hh"
#include "core/matrix4x4f.hh"

Matrix4x4f Matrix4x4f::model_rotate(const Matrix4x4f &model, const float angle, const Vector3f &axis)
{
    auto cv = std::cos(angle);
    auto sv = std::sin(angle);
    
    auto ax = Vector3f::normalized(axis);
    auto tm = Vector3f(ax * (1.0f - cv));
    
    auto rotation = Matrix4x4f::zero();
	rotation.D0.x = cv + tm.x * ax.x;
	rotation.D0.y = tm.x * ax.y + sv * ax.z;
	rotation.D0.z = tm.x * ax.z - sv * ax.y;
	rotation.D1.x = tm.y * ax.x - sv * ax.z;
	rotation.D1.y = cv + tm.y * ax.y;
	rotation.D1.z = tm.y * ax.z + sv * ax.x;
	rotation.D2.x = tm.z * ax.x + sv * ax.y;
	rotation.D2.y = tm.z * ax.y - sv * ax.x;
	rotation.D2.z = cv + tm.z * ax.z;

    auto result = Matrix4x4f::zero();
    result.D0 = model.D0 * rotation.D0.x + model.D1 * rotation.D0.y + model.D2 * rotation.D0.z;
    result.D1 = model.D0 * rotation.D1.x + model.D1 * rotation.D1.y + model.D2 * rotation.D1.z;
    result.D2 = model.D0 * rotation.D2.x + model.D1 * rotation.D2.y + model.D2 * rotation.D2.z;
    result.D3 = model.D3;
    return result;
}

Matrix4x4f Matrix4x4f::proj_ortho(float left, float right, float bottom, float top, float z_near, float z_far)
{
    auto result = Matrix4x4f::identity();
    result.D0.x = 2.0f / (right - left);
    result.D1.y = 2.0f / (top - bottom);
    result.D2.z = 1.0f / (z_far - z_near);
    result.D3.x = -1.0f * (right + left) / (right - left);
    result.D3.y = -1.0f * (top + bottom) / (top - bottom);
    result.D3.z = -1.0f * z_near / (z_far - z_near);
    return result;
}

Matrix4x4f Matrix4x4f::proj_persp(float y_fov, float aspect, float z_near, float z_far)
{
    auto inv_z_delta = 1.0f / (z_far - z_near);
    auto tan_half_fov = std::tan(0.5f * y_fov);

    auto result = Matrix4x4f::zero();
    result.D0.x = 1.0f / (aspect * tan_half_fov);
    result.D1.y = 1.0f / (tan_half_fov);
    result.D2.z = -1.0f * (z_far + z_near) * inv_z_delta;
    result.D2.w = -1.0f;
    result.D3.z = -2.0f * z_far * z_near * inv_z_delta;
    return result;
}

Matrix4x4f Matrix4x4f::view_psrc(const Vector3f &position, const Vector3angles &angles)
{
    Vector3f forward, up;
    Vector3angles::vectors(angles, &forward, nullptr, &up);

    auto result = Matrix4x4f::identity();
    result.D0.x = forward.y * up.z - forward.z * up.y;
    result.D1.x = forward.z * up.x - forward.x * up.z;
    result.D2.x = forward.x * up.y - forward.y * up.x;
    result.D3.x = -result.D0.x * position.x - result.D1.x * position.y - result.D2.x * position.z;
    result.D0.y = up.x;
    result.D1.y = up.y;
    result.D2.y = up.z;
    result.D3.y = -up.x * position.x - up.y * position.y - up.z * position.z;
    result.D0.z = -forward.x;
    result.D1.z = -forward.y;
    result.D2.z = -forward.z;
    result.D3.z = forward.x * position.x + forward.y * position.y + forward.z * position.z;
    return result;
}
