#include <iostream>
#include "raytracing/Raytracer.hpp"
#include "objects/Sphere.hpp"
#include "objects/Triangle.hpp"
#include "export/OBJ.hpp"

int main(int argc, char *argv[]) {
	std::cout << "Working Build system perchance?";

	Raytracer r(1920*4,1080*4);
	r.addObject (
		std::make_unique<Sphere>(
			MaterialInfo{Vector3(0,0,0), Vector3(1,1,1), 0.0f, 15.0f},
			Vector3(0, 7, 10), 
			5
		)
	);

	
	r.addObject(
        std::make_unique<Sphere>(
            MaterialInfo{Vector3(0.85f,0.1f,0.1f), Vector3(0,0,0), 0.0f, 0.0f},
            Vector3(0,0,10),
            1.5f
        )
    );

	r.addObject(
		std::make_unique<Sphere>(
			MaterialInfo{Vector3(0.1f,0.85f,0.1f), Vector3(), 0.0f, 0.0f},
			Vector3(3.5,-0.3f,10), 
			1.5f
		)
	);
	
	
	r.addObject(
		std::make_unique<Sphere>(
			MaterialInfo{Vector3(0.1f,0.1f,0.85f), Vector3(), 0.0f, 0.0f},
			Vector3(-3.5,-0.3f,10), 
			1.5f
		)
	);

	/*
	r.addObject(
		std::make_unique<Triangle>(
			MaterialInfo{Vector3(0.8f, 0.8f, 0.8f), Vector3(0,0,0), 0.0f, 0.0f},
			Vector3(-3, -3, 12),
			Vector3( 3, -3, 12),
			Vector3( 0,  3, 12)
		)
	);
	

	loadOBJ("model.obj", r,
		MaterialInfo{Vector3(0.8f, 0.2f, 0.2f), Vector3(), 0.5f, 0.0f},
		Transform{
			Vector3(-2, -0.03f, 5.1f),
			Vector3(0.03, 0.03, 0.03) 
		}
	);
	*/

	r.addObject(
		std::make_unique<Sphere>(
			MaterialInfo{Vector3(0.8, 0.8, 0.8), Vector3(0,0,0), 0.0f},
			Vector3(0, -21.5f, 10),
			20
		)
	);

	r.render(32, 7);

	return 0;
}
