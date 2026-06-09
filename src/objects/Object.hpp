#pragma once
#include "../math/Ray.hpp"

struct MaterialInfo {
	Vector3 color;
	float emissionStrength;
};

struct HitInfo {
	bool didHit;
	Vector3 hitPoint;
	const MaterialInfo* material = nullptr;
};

class Object {
public:
    Object(const MaterialInfo& m, const Vector3& p) : material(m), position(p) {}

    virtual HitInfo collision(const Ray& ray) const = 0;
    virtual ~Object() = default;

	MaterialInfo material;
	Vector3 position;
};
