#include <limits>
#include <vector>
#include <memory>
#include "../export/PPM.hpp"
#include "../math/Ray.hpp"
#include "../math/Vector3.hpp"
#include "../objects/Object.hpp"
#include "../objects/Sphere.hpp"
#include "Raytracer.hpp"

void Raytracer::render() {
	objects.push_back(
		std::make_unique<Sphere>(
			MaterialInfo{Vector3(1,0,0), 0.0f}, 
			Vector3(0,0,10),
			1.5f
		)
	);

	objects.push_back(
		std::make_unique<Sphere>(
			MaterialInfo{Vector3(0,1,0), 0.0f},
			Vector3(3.5,0,10), 
			1.5f
		)
	);
	
	objects.push_back(
		std::make_unique<Sphere>(
			MaterialInfo{Vector3(0,0,1), 0.0f},
			Vector3(-3.5,0,10), 
			1.5f
		)
	);

	float aspect = 1920.0f / 1080.0f;
	float scale = 1.0f;

	int max_bounce = 3;
	
	for (int y = 0; y < 1080; y++) {
		for (int x = 0; x < 1920; x++) {
			float ndcX = (x + 0.5f) / 1920.0f;
			float ndcY = (y + 0.5f) / 1080.0f;
	
			float screenX = (2.0f * ndcX - 1.0f) * aspect * scale;
			float screenY = (1.0f - 2.0f * ndcY) * scale;
	
			Vector3 pixel(screenX, screenY, 0);
			Ray r(camera, (pixel - camera).normalized());
	
			bool hit = false;
			const Vector3 *c;
	
			// Do raytracing
			for (int i = 0; i <= max_bounce; i++) {
				HitInfo hitInfo = getCollisions(r);
				if (hitInfo.didHit) {
					hit = true;
					Vector3 color = hitInfo.material->color;
					c = &hitInfo.material->color;
				}
				else {
					hit = false;
					break;
				}
			}
	
			image.setPixel(x, y, hit ? *c : Vector3(0,0,0));
		}
	}

	image.write("output.ppm");

}

HitInfo Raytracer::getCollisions(Ray& ray) {
	HitInfo bestHit{
		false,
		Vector3(),
		nullptr
	};

	float closestDistance = std::numeric_limits<float>::max();

	for (const auto& obj : objects) {
		HitInfo h = obj->collision(ray);

		if (!h.didHit)
			continue;

		float distance = (h.hitPoint - ray.origin).length();

		if (distance < closestDistance) {
			closestDistance = distance;
			bestHit = h;
		}
	}

	return bestHit;
}
