#include "Camera.h"

Ray Camera::createRay(glm::ivec2 _winPos)
{
	Ray newRay;
	// Setting the origin of the ray to the pixel position on the window
	newRay.origin = glm::vec3(_winPos.x, _winPos.y, 0);
	newRay.direction = glm::vec3(-1, 0, 0);

	return newRay;
}