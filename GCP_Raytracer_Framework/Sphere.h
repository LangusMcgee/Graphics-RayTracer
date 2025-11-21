#pragma once
#include "GLM/glm.hpp"
#include "Ray.h"

class Sphere
{
public:
	bool intersect(Ray _ray, glm::vec3& _intersectPos);
private:
	glm::vec3 m_position;
	float m_radius;
};