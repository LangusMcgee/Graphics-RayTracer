#pragma once
#include "GLM/glm.hpp"
#include "transform.h"
#include "Ray.h"

class Sphere
{
public:
	Sphere(glm::vec3 _pos, glm::vec3 _colour, float _rad) : 
		m_colour(_colour),
		m_radius(_rad) 
	{
		transform.position(_pos);
	};

	bool intersect(Ray _ray, glm::vec3& _intersectPos);

	void radius(float _rad) { m_radius = _rad; }

	glm::vec3 position() { return m_position; }

	void position(glm::vec3 _pos) { m_position = _pos; }

	glm::vec3 colour(){return m_colour;}

	void colour(glm::vec3 _colour){m_colour = _colour;}

	glm::vec3 get_normal(glm::vec3 pos);

	glm::vec3 shade(glm::vec3 _viewPos, glm::vec3 _hitPos);

	Transform transform;

private:
	glm::vec3 m_colour;
	float m_radius;
};