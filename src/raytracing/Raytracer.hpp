#pragma once
#include <vector>
#include <memory>
#include "../export/PPM.hpp"
#include "../math/Vector3.hpp"
#include "../objects/Object.hpp"

class Raytracer {
public:
	Raytracer(int w, int h) : width(w), height(h) {};
	void addObject(std::unique_ptr<Object> obj);
	void render(int samples, int bounces);

	int width;
	int height;
private:
	
	HitInfo getCollisions(Ray& ray);
	Vector3 getRandomDirection();
	Vector3 getRandomDirectionByNormal(Vector3& normal);
	Vector3 getEnvironmentalLighting(Ray& ray);
	Vector3 trace(Ray& ray, int maxBounce);
	Vector3 reflect(Ray& ray, Vector3& normal);
	
	PPM image{width, height};
	Vector3 camera{0, 0, -5};
	std::vector<std::unique_ptr<Object>> objects;
	};
