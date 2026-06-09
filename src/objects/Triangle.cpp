#include "Triangle.hpp"

#define EPSILON 1e-6f

HitInfo Triangle::collision(const Ray& ray) const {
    const Vector3& v0 = position;
    Vector3 edge1 = v1 - v0;
    Vector3 edge2 = v2 - v0;

    Vector3 h = ray.direction.cross(edge2);
    float det = edge1.dot(h);

    if (det > -EPSILON && det < EPSILON)
        return {false, Vector3(), Vector3(), nullptr};

    float invDet = 1.0f / det;
    Vector3 s = ray.origin - v0;
    float u = invDet * s.dot(h);

    if (u < 0.0f || u > 1.0f)
        return {false, Vector3(), Vector3(), nullptr};

    Vector3 q = s.cross(edge1);
    float v = invDet * ray.direction.dot(q);

    if (v < 0.0f || u + v > 1.0f)
        return {false, Vector3(), Vector3(), nullptr};

    float t = invDet * edge2.dot(q);

    if (t < EPSILON)
        return {false, Vector3(), Vector3(), nullptr};

    Vector3 hitPoint = ray.origin + ray.direction * t;
    Vector3 normal = edge1.cross(edge2).normalized();

    return {
        true,
        hitPoint,
        normal,
        &material
    };
}
