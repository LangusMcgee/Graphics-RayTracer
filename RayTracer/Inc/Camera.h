#pragma once
#include "Ray.h"
#include "transform.h"


class Camera
{
public:
	Camera();
	Ray createRay(glm::ivec2 _winPos);
	void setResolution(int _x, int _y);
	Transform transform;
	//void translate
private:
	glm::ivec2 resolution;

	float aspectRatio;
	float fov = 75;

	//glm::vec3 position;
	//glm::vec3 direction;
};