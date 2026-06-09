#include "Ray.hpp"

Ray::Ray() : origin(), direction(0, 0, 1) {}
Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin(origin), direction(direction) {}

Vector3 Ray::at(float t) const {
    return origin + direction * t;
}
