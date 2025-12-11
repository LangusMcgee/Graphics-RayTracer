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

	virtual bool intersect(Ray _ray, glm::vec3& _intersectPos) = 0;

	virtual glm::vec3 get_normal(glm::vec3 pos) = 0;

	virtual glm::vec3 shade(glm::vec3 _viewPos, glm::vec3 _hitPos, scene &_scene, int _recursion);

	bool shadowRayTest(float lightDist, glm::vec3 _intersectPos, Ray _shadowRay, scene& _scene);

	glm::vec3 getIndirectLighting(glm::vec3 _intersectPos, glm::vec3 _normal, int _samples, int _recursion, scene& _scene);

	glm::vec3 getRandomPointOnLight(std::shared_ptr<light> _light);

	Transform transform;

protected:
	glm::vec3 m_colour;
};