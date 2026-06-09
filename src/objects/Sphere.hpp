#pragma once
#include "Object.hpp"

class Sphere : public Object {
	public:
		Sphere(const MaterialInfo& m, const Vector3& p, const float r) : Object(m, p), radius(r) {}
		HitInfo collision(const Ray& ray) const override;

	private:
		float radius;
};
