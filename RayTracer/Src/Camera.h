#pragma once
#include "Ray.h"

class Camera
{
public:
	Camera();
	Ray createRay(glm::ivec2 _winPos);
private:	
	glm::vec3 position;
	glm::vec3 direction;
};