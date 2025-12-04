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
	bool is_in_shadow(glm::vec3 origin, glm::vec3 lightPos);
private:
	std::vector<std::shared_ptr<surface>> object_list;
};