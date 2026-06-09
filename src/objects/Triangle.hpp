#pragma once
#include "Object.hpp"

class Triangle : public Object {
	public:
	    Triangle(const MaterialInfo& m, const Vector3& a, const Vector3& b, const Vector3& c)
	        : Object(m, a), v1(b), v2(c) {}  // v0 = position (inherited)
	    HitInfo collision(const Ray& ray) const override;
	private:
	    Vector3 v1, v2;  // v0 is inherited `position`
};
