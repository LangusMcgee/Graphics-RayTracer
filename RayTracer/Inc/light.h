#pragma once
#include <GLM/glm.hpp>
#include "transform.h"
#include "Ray.h"

// A simple structure that represents a light
struct light
{
    light() :
        color(glm::vec3(0)),
        radius(1)
    {
        transform.position(glm::vec3(0));
    }

    light(glm::vec3 _pos, glm::vec3 _colour, float _rad) : 
        color (_colour),
        radius(_rad) 
    {
        transform.position(_pos);
    }

	Transform transform;
    glm::vec3 color;
    float radius;
};