#pragma once
#include "GLM/glm.hpp"
#include "Ray.h"

class Sphere
{
public:
	bool intersect(Ray _ray, glm::vec3& _intersectPos);

	void radius(float _rad) { m_radius = _rad; }

	void position(glm::vec3 _pos) { m_position = _pos; }

	glm::vec3 colour(){return m_colour;}

	void colour(glm::vec3 _colour){m_colour = _colour;}

private:
	glm::vec3 m_position;
	glm::vec3 m_colour;
	float m_radius;
};