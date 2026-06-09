#pragma once
#include <vector>
#include <memory>
#include "../export/PPM.hpp"
#include "../math/Vector3.hpp"
#include "../objects/Object.hpp"

class Raytracer {
public:
	void render();
private:
	
	HitInfo getCollisions(Ray& ray);

	PPM image{1920, 1080};
	Vector3 camera{0, 0, -5};
	std::vector<std::unique_ptr<Object>> objects;
};
