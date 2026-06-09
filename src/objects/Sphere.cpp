#include "Sphere.hpp"
#include <cmath>

HitInfo Sphere::collision(const Ray& ray) const {
	Vector3 oc = ray.origin - position;

	float a = ray.direction.dot(ray.direction);
	float b = 2.0f * oc.dot(ray.direction);
	float c = oc.dot(oc) - radius * radius;

	float discriminant = b * b - 4.0f * a * c;

	if (discriminant < 0.0f)
		return {false, Vector3(), Vector3(), nullptr};

	float sqrtD = sqrtf(discriminant);

	float t0 = (-b - sqrtD) / (2.0f * a);
	float t1 = (-b + sqrtD) / (2.0f * a);

	float t = t0;

	if (t < 0.0f)
		t = t1;

	if (t < 0.0f)
		return {false, Vector3(), Vector3(), nullptr};

	Vector3 hitPoint = ray.origin + ray.direction * t;
	Vector3 normal = (hitPoint - this->position).normalized();

	return {
		true,
		hitPoint,
		normal,
		&material
	};
}
