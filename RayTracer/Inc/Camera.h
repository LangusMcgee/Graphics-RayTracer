#pragma once
#include "Ray.h"

class Transform {};

class Camera
{
public:
	Camera();
	Ray createRay(glm::ivec2 _winPos);

	void rotate(float _pitch, float _yaw, float _roll);

	Transform transform;
	//void translate
private:	
	glm::vec3 position;
	glm::vec3 direction;
};