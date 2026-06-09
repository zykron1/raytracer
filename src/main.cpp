#include <iostream>
#include "raytracing/Raytracer.hpp"

int main(int argc, char *argv[]) {
	std::cout << "Working Build system perchance?";

	Raytracer r(1920,1080);
	r.render(512, 6);

	return 0;
}
