#pragma once
#include <GLM/glm.hpp>

class surface
{
public:
	surface(){}
	glm::vec3 shade(glm::vec3 _viewPos, glm::vec3 _hitPos);
};