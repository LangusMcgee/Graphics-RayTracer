#pragma once
#include <GLM/glm.hpp>

// A simple structure that represents a light
struct Light
{
    glm::vec3 position;
    glm::vec3 color;
    float intensity;
};