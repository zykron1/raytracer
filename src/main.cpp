#include <iostream>
#include <vector>
#include <memory>
#include "export/PPM.hpp"
#include "math/Ray.hpp"
#include "math/Vector3.hpp"
#include "objects/Object.hpp"
#include "objects/Sphere.hpp"

int main(int argc, char *argv[]) {
	std::cout << "Working Build system perchance?";
	PPM image(1920, 1080);

	Vector3 camera(0, 0, -5);

	std::vector<std::unique_ptr<Object>> objects;

	objects.push_back(
		std::make_unique<Sphere>(
			Vector3(1,0,0),
			Vector3(0,0,10), 
			2.0f
		)
	);

	objects.push_back(
		std::make_unique<Sphere>(
			Vector3(0,1,0),
			Vector3(5,0,10), 
			2.0f
		)
	);

	objects.push_back(
		std::make_unique<Sphere>(
			Vector3(0,0,1),
			Vector3(-5,0,10), 
			2.0f
		)
	);


	float aspect = 1920.0f / 1080.0f;
	float scale = 1.0f;
	
	for (int y = 0; y < 1080; y++) {
		for (int x = 0; x < 1920; x++) {
			float ndcX = (x + 0.5f) / 1920.0f;
			float ndcY = (y + 0.5f) / 1080.0f;
	
			float screenX = (2.0f * ndcX - 1.0f) * aspect * scale;
			float screenY = (1.0f - 2.0f * ndcY) * scale;
	
			Vector3 pixel(screenX, screenY, 0);
			Ray r(camera, (pixel - camera).normalized());
	
			bool hit = false;
			Vector3 *c;
	
			for (const auto& obj : objects) {
				if (obj->collision(r)) {
					hit = true;
					c = &obj->color;
					break;
				}
			}
	
			image.setPixel(x, y, hit ? *c : Vector3(0,0,0));
		}
	}

	image.write("output.ppm");

	return 0;
}
