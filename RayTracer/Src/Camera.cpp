#include "Camera.h"


Camera::Camera()// : position(0.0f)
{
	setResolution(1920, 1080);
}

void Camera::setResolution(int _x, int _y)
{
	resolution.x = _x;
	resolution.y = _y;

	aspectRatio = float(_x) / float(_y);
}

Ray Camera::createRay(glm::vec2 _winPos)
{
	// Convert pixel coordinates to normalized screen space
	float u = (_winPos.x) / float(resolution.x);
	float v = (_winPos.y) / float(resolution.y);

	// Map normalized coordinates to ndc space
	// Apply aspect ratio and field of view to get correct perspective
	float x = (2.0f * u - 1.0f) * aspectRatio *tan(fov * 0.5f);
	float y = -(2.0f * v - 1.0f) * tan(fov * 0.5f);

	// Ray direction in view space
	// Camera looks down the negative Z axis
	glm::vec3 camDir = glm::normalize(glm::vec3(x, y, -1.0f));

	// Camera-to-world transform matrix
	glm::mat4 camToWorld = transform.model_matrix();

	Ray newRay;
	
	// Transform ray origin from camera space to world space
	newRay.origin = glm::vec3(camToWorld * glm::vec4(0, 0, 0, 1));

	// Transform ray direction into world space
	// w = 0 ensures no translation is applied
	newRay.direction = glm::normalize(glm::vec3(camToWorld * glm::vec4(camDir, 0)));

	return newRay;
}