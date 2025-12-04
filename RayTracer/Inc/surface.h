#pragma once
#include <GLM/glm.hpp>
#include <transform.h>
#include <Ray.h>

class surface
{
public:
	surface(){}
	virtual ~surface() = default;

	virtual bool intersect(Ray _ray, glm::vec3& _intersectPos) = 0;

	virtual glm::vec3 get_normal(glm::vec3 pos) = 0;

	virtual glm::vec3 shade(glm::vec3 _viewPos, glm::vec3 _hitPos) = 0;

	Transform transform;
};