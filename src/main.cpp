#include <iostream>
#include "export/PPM.hpp"
#include "math/Vector3.hpp"

int main(int argc, char *argv[]) {
	std::cout << "Working Build system perchance?";
	PPM image(1920, 1080);
	Vector3 red(1.0f, 0.0f, 0.0f);

	for (int y = 0; y < 1080; y++) {
		for (int x = 0; x < 1920; x++) {
			image.setPixel(x, y, red);
		}
	}

	image.write("output.ppm");

	return 0;
}
