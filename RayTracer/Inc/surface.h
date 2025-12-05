#pragma once
#include <GLM/glm.hpp>
#include <transform.h>
#include <Ray.h>


class scene;
class surface
{
public:
	surface(){}
	virtual ~surface() = default;

	virtual bool intersect(Ray _ray, glm::vec3& _intersectPos) = 0;

	virtual glm::vec3 get_normal(glm::vec3 pos) = 0;

	virtual glm::vec3 shade(glm::vec3 _viewPos, glm::vec3 _hitPos, scene &_scene) = 0;

	Transform transform;
};