#pragma once
#include <string>
#include <vector>
#include "../math/Vector3.hpp"

class PPM {
public:
    PPM(int width, int height);

    void setPixel(int x, int y, const Vector3& color);
    void write(const std::string& filename) const;

private:
    int width, height;
    std::vector<unsigned char> data;
};
