#pragma once
#include <vector>
#include "Sphere.h"
#include "Ray.h"

class ray_tracer
{
public:
	glm::vec3 trace_ray(Ray _ray);
private:
	std::vector<Sphere> sphere_list;
};