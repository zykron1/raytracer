#include "PPM.hpp"
#include <fstream>
#include <algorithm>

PPM::PPM(int width, int height)
    : width(width), height(height), data(width * height * 3, 0) {}

void PPM::setPixel(int x, int y, const Vector3& color) {
    int i = (y * width + x) * 3;

    auto clamp = [](float v) {
        return (unsigned char)(std::max(0.0f, std::min(1.0f, v)) * 255.0f);
    };

    data[i + 0] = clamp(color.x);
    data[i + 1] = clamp(color.y);
    data[i + 2] = clamp(color.z);
}

void PPM::write(const std::string& filename) const {
    std::ofstream file(filename, std::ios::binary);

    file << "P6\n" << width << " " << height << "\n255\n";
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
}
