#include "core/precompiled.hh"
#include "core/vector3f.hh"

float Vector3f::length(const Vector3f &vector)
{
    return std::sqrt(Vector3f::dot(vector, vector));
}

float Vector3f::length2(const Vector3f &vector)
{
    return Vector3f::dot(vector, vector);
}

Vector3f Vector3f::normalized(const Vector3f &vector)
{
    // Use the multiplication operator here because it's going
    // to only calculate the multiplier once and then won't use division
    return vector * (1.0f / Vector3f::length(vector));
}

float Vector3f::normalize(Vector3f &vector)
{
    float result = Vector3f::length(vector);
    float multiply = 1.0f / result;
    vector.x *= multiply;
    vector.y *= multiply;
    vector.z *= multiply;
    return result;
}
