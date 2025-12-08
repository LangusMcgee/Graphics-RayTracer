#include "RayTracer.h"
#include "surface.h"
#include "iostream"

bool ray_tracer::trace_ray(Ray _ray, glm::vec3 &_colour)
{
    float closestDist = FLT_MAX;
    bool intersection = false;
    glm::vec3 closest_intersection;
    int sphere_index = -1;
    glm::vec3 colour;

    for (int i = 0; i < m_scene.object_list.size(); i++)
    {
        glm::vec3 intersect_pos(0);
        
        // Returns colour at closest intersection of the ray
        if ( m_scene.object_list[i]->intersect(_ray, intersect_pos))
        {
            float dist = glm::distance(_ray.origin, intersect_pos);
            if (dist < closestDist)
            {
                closestDist = dist;
                closest_intersection = intersect_pos;
                sphere_index = i;
                colour = m_scene.object_list[i]->shade(_ray.origin, intersect_pos, m_scene, 5);
                // shoot shadow ray
                // add shadow on top of colour
                intersection = true;
            }
        }
    }

	if (intersection)
	{
		_colour = colour;
        return true;
	}
	else
		return false;
}

//void ray_tracer::addObject(std::shared_ptr<surface> _surface)
//{
//	object_list.push_back(_surface);
//}