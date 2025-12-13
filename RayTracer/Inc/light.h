#pragma once
#include <GLM/glm.hpp>
#include "transform.h"

// A simple structure that represents a light
struct light
{
    light() :
        position(glm::vec3(0)),
        color(glm::vec3(0)),
        radius(0) {}

    light(glm::vec3 _pos, glm::vec3 _colour, float _radius) : 
        position(_pos),
        color (_colour),
        radius(_radius) {}

    Transform transform;

    float radius;

    glm::vec3 position;
    glm::vec3 color;
    float intensity;
};