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

    bool rayIntersect(Ray _ray, glm::vec3& _intersectPos)
    {
        glm::vec3 p = transform.position(); // Sphere position
        glm::vec3 a = _ray.origin; // Ray origin
        glm::vec3 n = _ray.direction; // Ray Direction
        float r = radius; // Sphere radius

        if (glm::length(a - p) < r) // do not compute if origin inside sphere
        {
            return false;
        }

        float d = glm::length(p - a - (glm::dot((p - a), n) * n)); // Shortest distance from ray to sphere centre

        if (d >= r)
        {
            return false;
        }

        float x = glm::sqrt(glm::pow(r, 2) - glm::pow(d, 2)); // distance from closest point on ray to intersection point

        // Assign closest intersection
        _intersectPos = a + ((glm::dot(p - a, n) - x) * n);

        // check if intersection point is in front of the ray or not

        if (glm::dot(n, (p - a)) - x > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
	}

	Transform transform;
    glm::vec3 color;
    float radius;
};