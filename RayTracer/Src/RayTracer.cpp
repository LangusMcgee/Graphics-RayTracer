#include "RayTracer.h"
#include "iostream"

glm::vec3 ray_tracer::trace_ray(Ray _ray)
{
    float closestDist = FLT_MAX;
    bool intersection = false;
    glm::vec3 closest_intersection;
    int sphere_index = -1;
    glm::vec3 colour;

    for (int i = 0; i < sphere_list.size(); i++)
    {
        glm::vec3 intersect_pos(0);
        
        // Returns colour at closest intersection of the ray
        if (sphere_list[i]->intersect(_ray, intersect_pos))
        {
            float dist = glm::distance(_ray.origin, intersect_pos);

            if (dist < closestDist)
            {
                closestDist = dist;
                closest_intersection = intersect_pos;
                sphere_index = i;
                colour = sphere_list[i]->shade(_ray.origin, intersect_pos);
                intersection = true;
            }
        }
    }

	if (intersection)
	{
		return colour;
	}
	else
		return glm::vec3(0.7,0.7,1);
}

void ray_tracer::addSphere(std::shared_ptr<Sphere> _sphere)
{
	sphere_list.push_back(_sphere);
}