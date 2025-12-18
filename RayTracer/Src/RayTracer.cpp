#include "RayTracer.h"
#include "surface.h"
#include "iostream"

bool ray_tracer::trace_ray(Ray _ray, glm::vec3 &_colour) // -todo render distance param -Custom renderdist for first ray cast and then larger for in shade sampling
{
    float closestDist = FLT_MAX; // Starting value to compare with furthest intersection.
    bool intersection = false;
    glm::vec3 closest_intersection;
    glm::vec3 colour;

    for (int i = 0; i < m_scene.object_list.size(); i++)
    {
        glm::vec3 intersect_pos(0);
        
        // Returns colour at closest intersection of the ray
        if ( m_scene.object_list[i]->intersect(_ray, intersect_pos))
        {
            // Get the distance from the ray's origin to the point of intersection
            float dist = glm::distance(_ray.origin, intersect_pos);
            // Compare the intersection's distance with previous intersects to see what is infront
            if (dist < closestDist)
            {
                // if current sphere is closer than the prev closest, set it as closest
                closestDist = dist;
                closest_intersection = intersect_pos;
                colour = m_scene.object_list[i]->shade(_ray.origin, intersect_pos, m_scene, 5); // TODO - only shade when we know what object is closest
                intersection = true;
            }
        }
    }

	if (intersection)
	{
		_colour = colour; // return shaded colour to be drawn at pixel/added to AA sample
        return true;
	}
	else
        _colour = glm::vec3(0); // return black incase we want to debug - currently this colour is not in use.
		return false;
}

//void ray_tracer::addObject(std::shared_ptr<surface> _surface)
//{
//	object_list.push_back(_surface);
//}