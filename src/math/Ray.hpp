#pragma once
#include "Vector3.hpp"

class Ray {
public:
    Vector3 origin;
    Vector3 direction;

    Ray();
    Ray(const Vector3& origin, const Vector3& direction);

    Vector3 at(float t) const;
};
