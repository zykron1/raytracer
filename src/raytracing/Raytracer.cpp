#include <iostream>
#include <limits>
#include <vector>
#include <memory>
#include <random>
#include "../export/PPM.hpp"
#include "../math/Ray.hpp"
#include "../math/Vector3.hpp"
#include "../objects/Object.hpp"
#include "Raytracer.hpp"

void Raytracer::addObject(std::unique_ptr<Object> obj) {
	objects.push_back(std::move(obj));
}

void Raytracer::render(int samples, int bounces) {
	float aspect = (float)width/(float)height;
	float scale = 1.0f;

	int max_bounce = 3;
	
	#ifdef _OPENMP
	#pragma omp parallel for schedule(dynamic, 16) collapse(2)
	#endif

	for (int y = 0; y < height; y++) {
		std::cout << "PROGRESS:" << (100.0f*y/height) << "%\n";
		for (int x = 0; x < width; x++) {
			float ndcX = (x + 0.5f) / width;
			float ndcY = (y + 0.5f) / height;
	
			float screenX = (2.0f * ndcX - 1.0f) * aspect * scale;
			float screenY = (1.0f - 2.0f * ndcY) * scale;
	
			Vector3 pixel(screenX, screenY, 0);
	
			Vector3 c(0,0,0);

			for (int s = 0; s < samples; s++) {
				Ray r(camera, (pixel - camera).normalized());
				c += trace(r, bounces);
			}
			c = c * (1.0f / samples);
	
			image.setPixel(x, y, c);
		}
	}

	image.write("output.ppm");

}

HitInfo Raytracer::getCollisions(Ray& ray) {
	HitInfo bestHit{
		false,
		Vector3(),
		Vector3(),
		nullptr
	};

	float closestDistance = std::numeric_limits<float>::max();

	for (const auto& obj : objects) {
		HitInfo h = obj->collision(ray);

		if (!h.didHit)
			continue;

		float distance = (h.hitPoint - ray.origin).lengthSquared();

		if (distance < closestDistance) {
			closestDistance = distance;
			bestHit = h;
		}
	}

	return bestHit;
}


Vector3 Raytracer::getRandomDirection() {
	thread_local std::random_device rd;
    thread_local std::mt19937 gen{rd()};
    thread_local std::uniform_real_distribution<float> distrib{-1.0f, 1.0f};
	while (true) {
		Vector3 v(
			distrib(gen),
			distrib(gen),
			distrib(gen)
		);

		if (v.dot(v) <= 1.0f) {return v.normalized();}
	}
}


Vector3 Raytracer::getRandomDirectionByNormal(Vector3& normal) {
	Vector3 direction = this->getRandomDirection();
	if (direction.dot(normal) < 0) {
		return direction*-1;
	}

	return direction;
}

Vector3 Raytracer::trace(Ray& ray, int maxBounce) {
	Vector3 incomingLight(0,0,0);
	Vector3 rayColor(1,1,1);

	for (int i = 0; i < maxBounce; i++) {
		HitInfo hitInfo = this->getCollisions(ray);
		if (hitInfo.didHit) {
			ray.origin = hitInfo.hitPoint + hitInfo.normal * 0.001f;
			
			Vector3 diffuse = this->getRandomDirectionByNormal(hitInfo.normal);
			Vector3 specular = this->reflect(ray, hitInfo.normal);

			const MaterialInfo material = *hitInfo.material;

			ray.direction = diffuse * (1.0f - material.smoothness)
              + specular * material.smoothness;

			Vector3 emittedLight = material.emissionColor * material.emissionStrength;
			float strength = hitInfo.normal.dot(ray.direction);

			incomingLight += emittedLight * rayColor;
			// x2 bc lambart cosine law, halfs the power of light
			rayColor *= material.color * strength * 2;
		} else {
			incomingLight += rayColor * this->getEnvironmentalLighting(ray);
			break;
		}
	}

	return incomingLight;
}

Vector3 Raytracer::getEnvironmentalLighting(Ray& ray) {
	Vector3 dir = ray.direction.normalized();

	float t = 0.5f * (dir.y + 1.0f);

	Vector3 sky(0.5f, 0.7f, 1.0f);
	Vector3 ground(0.2f, 0.2f, 0.2f);

	return sky * t + ground * (1.0f - t);
}

Vector3 Raytracer::reflect(Ray& ray, Vector3& normal) {
	Vector3 d = ray.direction;
	Vector3 n = normal;

	float dotDN = d.dot(n);

	return d - n * (2.0f * dotDN);
}

