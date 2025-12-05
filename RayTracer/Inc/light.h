#pragma once
#include <GLM/glm.hpp>

// A simple structure that represents a light
struct light
{
    light() :
        position(glm::vec3(0)),
        color(glm::vec3(0)),
        intensity(0) {}

    light(glm::vec3 _pos, glm::vec3 _colour, float _intensity) : 
        position(_pos),
        color (_colour),
        intensity(_intensity) {}

    glm::vec3 position;
    glm::vec3 color;
    float intensity;
};