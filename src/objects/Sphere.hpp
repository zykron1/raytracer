#pragma once
#include "Object.hpp"

class Sphere : public Object {
	public:
		Sphere(const Vector3& c, const Vector3& p, const float r) : Object(c, p), radius(r) {}
		bool collision(const Ray& ray) const override;

	private:
		float radius;
};
