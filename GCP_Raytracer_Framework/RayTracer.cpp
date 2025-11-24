#include "RayTracer.h"
#include "iostream"

glm::vec3 ray_tracer::trace_ray(Ray _ray)
{
	glm::vec3 closest_intersection(0);

	bool intersection = false;
	int sphere_index = 0;

	//std::cout << sphere_list.size() << "\n";

	for (int i = 0; i < this->sphere_list.size(); i++)
	{
		glm::vec3 intersect_pos(0);


		if (sphere_list.at(i).intersect(_ray, intersect_pos))
		{
			std::cout << i << "\n";
			if (closest_intersection.length() > intersect_pos.length())
			{
				intersection = true;
				sphere_index = i;
				closest_intersection = intersect_pos;
			}
		}
	}

	if (intersection)
	{
		return this->sphere_list.at(sphere_index).colour();
	}
	else
		return glm::vec3(1, 1, 1);
}

void ray_tracer::addSphere(Sphere _sphere)
{
	sphere_list.push_back(_sphere);
}