#include "core/precompiled.hh"
#include "core/vector2f.hh"

float Vector2f::length(const Vector2f &vector)
{
    return std::sqrt(Vector2f::dot(vector, vector));
}

float Vector2f::length2(const Vector2f &vector)
{
    return Vector2f::dot(vector, vector);
}

Vector2f Vector2f::normalized(const Vector2f &vector)
{
    // Use the multiplication operator here because it's going
    // to only calculate the multiplier once and then won't use division
    return vector * (1.0f / Vector2f::length(vector));
}

float Vector2f::normalize(Vector2f &vector)
{
    float result = Vector2f::length(vector);
    float multiply = 1.0f / result;
    vector.x *= multiply;
    vector.y *= multiply;
    return result;
}
