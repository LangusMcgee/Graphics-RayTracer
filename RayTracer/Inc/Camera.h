#pragma once
#include "Ray.h"

class Transform {};

class Camera
{
public:
	Camera();
	Ray createRay(glm::ivec2 _winPos);

	Transform transform;
	//void translate
private:	
	glm::vec3 position;
	glm::vec3 direction;
};