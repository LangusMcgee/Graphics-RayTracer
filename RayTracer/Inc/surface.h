#pragma once
#include <GLM/glm.hpp>
#include <transform.h>
#include "light.h"
#include <memory>
#include <Ray.h>


class scene;
class surface
{
public:
	surface() {};
	virtual ~surface() = default;

//Virtual functions to allow for implementation with spheres, planes etc...
// 
	// Casts given ray and returns true if intersects with self
	virtual bool intersect(Ray _ray, glm::vec3& _intersectPos) = 0;

	virtual glm::vec3 get_normal(glm::vec3 pos) = 0;

	// Shades sphere at given intersection point returning a colour, same implementation for all surfaces
	virtual glm::vec3 shade(glm::vec3 _viewPos, glm::vec3 _hitPos, scene &_scene, int _recursion);

	// Test against area light to see if anything is between it and self.
	bool shadowRayTest(float lightDist, glm::vec3 _intersectPos, Ray _shadowRay, scene& _scene);

	// shoots out specified number of rays and accumulates the colour value of shaded intersections.
	glm::vec3 getIndirectLighting(glm::vec3 _intersectPos, glm::vec3 _normal, int _samples, int _recursion, scene& _scene);

	// Used for soft shadows, returns a point on the area light's sphere
	glm::vec3 getRandomPointOnLight(std::shared_ptr<light> _light);

	glm::vec3 randomInUnitSphere();

	// Checks if in shadow and returns lighting value if not (directly lit)
	glm::vec3 directLighting(glm::vec3 intersectPos, glm::vec3 normal, scene& _scene);

	Transform transform;

protected:
	// Colour of surface
	glm::vec3 m_colour;
};