#include "RayTracer.h"
#include "iostream"

glm::vec3 ray_tracer::trace_ray(Ray _ray)
{
	glm::vec3 closest_intersection(0);

	bool intersection = false;
	int sphere_index = 0;

	glm::vec3 colour;

	//std::cout << sphere_list.size() << "\n";

	for (int i = 0; i < this->sphere_list.size(); i++)
	{
		glm::vec3 intersect_pos(0);


		if (sphere_list[i].intersect(_ray, intersect_pos))
		{
			//std::cout << i << "\n";

			colour = sphere_list[i].shade(_ray.origin, intersect_pos);
			std::cout << "sphere " << i << std::endl;
			intersection = true;
			sphere_index = i;
			closest_intersection = intersect_pos;
		}
	}

	if (intersection)
	{
		return colour;
	}
	else
		return glm::vec3(0);
}

void ray_tracer::addSphere(Sphere _sphere)
{
	sphere_list.push_back(_sphere);
}