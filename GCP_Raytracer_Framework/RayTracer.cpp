#include "RayTracer.h"

glm::vec3 ray_tracer::trace_ray(Ray _ray)
{
	glm::vec3 closest_intersection(0);

	for (int i = 0; i < this->sphere_list.size(); i++)
	{
		glm::vec3 intersect_pos(0);
		glm::vec3 RGB(0);

		if (sphere_list.at(i).intersect(_ray, intersect_pos))
		{
			if (closest_intersection.length() > intersect_pos.length())
			{
				closest_intersection = intersect_pos;
			}
		}
	}
}