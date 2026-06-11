#include <fstream>
#include <sstream>
#include <iostream>
#include "../objects/Triangle.hpp"
#include "OBJ.hpp"

void loadOBJ(const std::string& path, Raytracer& r, const MaterialInfo& material, const Transform& transform) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file: " << path << std::endl;
        return;
    }

    std::vector<Vector3> vertices;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "v") {
            float x, y, z;
            iss >> x >> y >> z;

            Vector3 v(
                x * transform.scale.x    + transform.position.x,
                y * transform.scale.y    + transform.position.y,
                z * transform.scale.z    + transform.position.z
            );
            vertices.push_back(v);

        } else if (token == "f") {
            std::vector<int> indices;
            std::string faceToken;

            while (iss >> faceToken) {
                std::istringstream fss(faceToken);
                std::string indexStr;
                std::getline(fss, indexStr, '/');
                indices.push_back(std::stoi(indexStr));
            }

            for (int i = 1; i + 1 < (int)indices.size(); i++) {
                int i0 = indices[0]     - 1;
                int i1 = indices[i]     - 1;
                int i2 = indices[i + 1] - 1;

                if (i0 < 0 || i1 < 0 || i2 < 0 ||
                    i0 >= (int)vertices.size() ||
                    i1 >= (int)vertices.size() ||
                    i2 >= (int)vertices.size()) {
                    std::cerr << "OBJ face index out of range" << std::endl;
                    continue;
                }

                r.addObject(std::make_unique<Triangle>(
                    material,
                    vertices[i0],
                    vertices[i1],
                    vertices[i2]
                ));
            }
        }
    }

    std::cout << "Loaded " << vertices.size() << " vertices from " << path << std::endl;
}
