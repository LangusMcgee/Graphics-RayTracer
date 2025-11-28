#pragma once
#include "GLM/glm.hpp"
#include <iostream>

void print_vec3(glm::vec3 _vec3)
{
	std::cout << "X= " << _vec3.x << "  Y= " << _vec3.y << "  Z= " << _vec3.z << "\n";
}