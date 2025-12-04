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
	void addObject(std::shared_ptr<surface> _surface);
private:
	std::vector<std::shared_ptr<surface>> sphere_list;
};