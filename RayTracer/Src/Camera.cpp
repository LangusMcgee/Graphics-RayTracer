#include "Camera.h"


Camera::Camera() : position(0.0f)
{
	setResolution(1920, 1080);
}

void Camera::setResolution(int _x, int _y)
{
	resolution.x = _x;
	resolution.y = _y;

	aspectRatio = float(_x) / float(_y);
}

Ray Camera::createRay(glm::ivec2 _winPos)
{
	float u = (_winPos.x + 0.5f) / float(resolution.x);
	float v = (_winPos.y + 0.5f) / float(resolution.y);

	float x = (2.0f * u - 1.0f) * aspectRatio *tan(fov * 0.5f);
	float y = -(2.0f * v - 1.0f) * tan(fov * 0.5f);

	glm::vec3 camDir = glm::normalize(glm::vec3(x, y, -1.0f));

	glm::mat4 camToWorld = transform.model_matrix();

	Ray newRay;
	
	newRay.origin = glm::vec3(camToWorld * glm::vec4(0, 0, 0, 1));

	newRay.direction = glm::normalize(glm::vec3(camToWorld * glm::vec4(camDir, 0)));

	return newRay;
}