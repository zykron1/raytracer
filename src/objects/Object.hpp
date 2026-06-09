#pragma once
#include "../math/Ray.hpp"

class Object {
public:
    Object(const Vector3& c, const Vector3& p) : color(c), position(p) {}

    virtual bool collision(const Ray& ray) const = 0;
    virtual ~Object() = default;

    Vector3 color;
	Vector3 position;
};
