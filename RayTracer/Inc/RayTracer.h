#pragma once
#include <vector>
#include <memory>
#include "Sphere.h"
#include "Ray.h"

class ray_tracer
{
public:
	glm::vec3 trace_ray(Ray _ray);
	void addSphere(std::shared_ptr<Sphere> _sphere);
private:
	std::vector<std::shared_ptr<Sphere>> sphere_list;
};