#include "Sphere.h"
#include "scene.h"

bool Sphere::intersect(Ray _ray, glm::vec3 &_intersectPos)
{
	glm::vec3 p = transform.position(); // Sphere position
	glm::vec3 a = _ray.origin; // Ray origin
	glm::vec3 n = _ray.direction; // Ray Direction
	float r = m_radius; // Sphere radius

	if (glm::length(a - p) < r) // do not compute if origin inside sphere
	{
		return false;
	}

	float d = glm::length(p - a - (glm::dot((p - a), n) * n)); // Shortest distance from ray to sphere centre

	if (d >= r)
	{
		return false;
	}

	float x = glm::sqrt(glm::pow(r, 2) - glm::pow(d, 2)); // distance from closest point on ray to intersection point

	// Assign closest intersection
	_intersectPos = a + ((glm::dot(p - a, n) - x) * n);

	return true;
}

glm::vec3 Sphere::get_normal(glm::vec3 _intersectPos)
{	
	return glm::normalize(_intersectPos - transform.position());
}


glm::vec3 Sphere::shade(glm::vec3 _viewPos, glm::vec3 _intersectPos, scene& _scene)
{
    glm::vec3 normal = get_normal(_intersectPos);

    glm::vec3 diffuse = glm::vec3(0.0f);
    glm::vec3 specular = glm::vec3(0.0f);

    glm::vec3 shadow_ray_intersect;
    glm::vec3 ambient_colour = m_colour * 0.1f;

    // iterate through each light
    for (int i = 0; i < _scene.light_list.size(); i++)
    {
        // get the light direction and distance
        glm::vec3 lightDir = normalize(_scene.light_list[i]->position - _intersectPos);
        float lightDist = glm::distance(_scene.light_list[i]->position, _intersectPos);

        bool blocked = false;

        // shadow ray
        Ray shadow_ray(_intersectPos + normal * 0.0001f, lightDir);

        // check for occluders
        for (int x = 0; x < _scene.object_list.size(); x++)
        {
            if (_scene.object_list[x].get() == this)
                continue;

            if (_scene.object_list[x]->intersect(shadow_ray, shadow_ray_intersect))
            {
                float hitDist = glm::distance(_intersectPos, shadow_ray_intersect);
                if (hitDist < lightDist)
                {
                    blocked = true;
                    break;
                }
            }
        }

        // diffuse
        float NdotL = glm::max(glm::dot(normal, lightDir), 0.0f);
        glm::vec3 diffuse_contribution = m_colour * NdotL;

        if (blocked)
            diffuse_contribution *= glm::vec3(0.2f);

        diffuse += diffuse_contribution;

        // specular
        glm::vec3 viewDir = glm::normalize(_viewPos - _intersectPos);
        glm::vec3 reflectDir = reflect(-lightDir, normal);

        float spec = pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f), 32.0f);
        glm::vec3 specularColor(1.0f, 1.0f, 0.5f);

        specular += spec * specularColor;
    }

    // final color
    return ambient_colour + diffuse + specular;
}
