#pragma once
#include <GLM/glm.hpp>
#include <transform.h>
#include <Ray.h>

class surface
{
public:
	surface(){}
	virtual bool intersect(Ray _ray, glm::vec3& _intersectPos);

	virtual glm::vec3 get_normal(glm::vec3 pos);



	virtual glm::vec3 shade(glm::vec3 _viewPos, glm::vec3 _hitPos);

	Transform transform;

private:

};