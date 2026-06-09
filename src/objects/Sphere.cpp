#include "Sphere.hpp"

bool Sphere::collision(const Ray& ray) const {
    Vector3 oc = ray.origin - position;

    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * oc.dot(ray.direction);
    float c = oc.dot(oc) - radius * radius;

    float discriminant = b * b - 4.0f * a * c;

    return discriminant >= 0.0f;
}
