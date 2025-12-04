#pragma once
#include <vector>
#include <memory>
#include "Sphere.h"
#include <GLM/glm.hpp>
#include "Ray.h"

class ray_tracer
{
public:
	bool trace_ray(Ray _ray, glm::vec3 &_colour);
	void addSphere(std::shared_ptr<Sphere> _sphere);
private:
	std::vector<std::shared_ptr<Sphere>> sphere_list;
};