#include "core/precompiled.hh"
#include "core/vector3angles.hh"

Vector3angles Vector3angles::wrap_180(const Vector3angles &angles)
{
    constexpr float A180 = cxpr::radians(180.0f);
    constexpr float A360 = cxpr::radians(360.0f);

    Vector3angles result;
    result.x = std::fmod(angles.x + A180, A360);
    result.y = std::fmod(angles.y + A180, A360);
    result.z = std::fmod(angles.z + A180, A360);

    result.x = ((result.x < 0.0f) ? (result.x + A360) : result.x) - A180;
    result.y = ((result.y < 0.0f) ? (result.y + A360) : result.y) - A180;
    result.z = ((result.z < 0.0f) ? (result.z + A360) : result.z) - A180;

    return result;
}

Vector3angles Vector3angles::wrap_360(const Vector3angles &angles)
{
    constexpr float A360 = cxpr::radians(360.0f);

    Vector3angles result;
    result.x = std::fmod(std::fmod(angles.x, A360) + A360, A360);
    result.y = std::fmod(std::fmod(angles.y, A360) + A360, A360);
    result.z = std::fmod(std::fmod(angles.z, A360) + A360, A360);
    return result;
}

Vector3f Vector3angles::cos(const Vector3angles &angles)
{
    Vector3f result;
    result.x = std::cos(angles.x);
    result.y = std::cos(angles.y);
    result.z = std::cos(angles.z);
    return result;
}

Vector3f Vector3angles::sin(const Vector3angles &angles)
{
    Vector3f result;
    result.x = std::sin(angles.x);
    result.y = std::sin(angles.y);
    result.z = std::sin(angles.z);
    return result;
}

void Vector3angles::vectors(const Vector3angles &angles, Vector3f &forward)
{
    const float cosp = std::cos(angles.x);
    const float cosy = std::cos(angles.y);
    const float sinp = std::sin(angles.x);
    const float siny = std::sin(angles.y);

    forward.x = cosp * siny * (-1.0f);
    forward.y = sinp;
    forward.z = cosp * cosy * (-1.0f);
}

void Vector3angles::vectors(const Vector3angles &angles, Vector3f *forward, Vector3f *right, Vector3f *up)
{
    if(!forward && !right && !up) {
        // There's no point in figuring out
        // direction vectors if nothing is passed
        // in the function to store that stuff in
        return;
    }

    auto pcv = Vector3angles::cos(angles);
    auto psv = Vector3angles::sin(angles);
    auto ncv = pcv * (-1.0f);
    auto nsv = psv * (-1.0f);

    if(forward) {
        forward->x = pcv.x * nsv.y;
        forward->y = psv.x;
        forward->z = pcv.x * ncv.y;
    }

    if(right) {
        right->x = pcv.z * pcv.y;
        right->y = psv.z * pcv.y;
        right->z = nsv.y;
    }

    if(up) {
        up->x = psv.x * psv.y * pcv.z + ncv.y * psv.z;
        up->y = pcv.x * pcv.z;
        up->z = nsv.x * ncv.y * pcv.z + psv.y * psv.z;
    }
}
