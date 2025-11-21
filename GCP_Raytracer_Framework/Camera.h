#pragma once
#include "Ray.h"

class Camera
{
public:
	Ray createRay(glm::ivec2 _winPos);
private:

};