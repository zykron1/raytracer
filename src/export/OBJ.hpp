#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../objects/Object.hpp"

struct Transform {
    Vector3 position = Vector3(0, 0, 0);
    Vector3 scale    = Vector3(1, 1, 1);
};

void loadOBJ(const std::string& path, std::vector<std::unique_ptr<Object>>& objects, const MaterialInfo& material, const Transform& transform = Transform{});
