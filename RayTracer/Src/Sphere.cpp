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
    glm::vec3 N = get_normal(_intersectPos);
    glm::vec3 baseColor = m_colour;

    glm::vec3 finalColor(0.0f);

    // Loop over all lights
    for (int i = 0; i < _scene.light_list.size(); i++)
    {
        glm::vec3 lightPos = _scene.light_list[i]->position;
        glm::vec3 lightDir = normalize(lightPos - _intersectPos);
        float lightDist = glm::distance(lightPos, _intersectPos);

        // -------- SHADOW RAY --------
        bool inShadow = false;
        glm::vec3 shadowHit;

        // Offset origin to avoid self-shadowing
        Ray shadowRay(_intersectPos + N * 0.001f, lightDir);

        for (int x = 0; x < _scene.object_list.size(); x++)
        {
            if (_scene.object_list[x]->intersect(shadowRay, shadowHit))
            {
                float hitDist = glm::distance(_intersectPos, shadowHit);

                // If the object is between the point and the light ? shadow
                if (hitDist < lightDist)
                {
                    inShadow = true;
                    break;
                }
            }
        }

        // -------- DIFFUSE LIGHTING --------
        float NdotL = glm::max(glm::dot(N, lightDir), 0.0f);

        // If shadowed ? darken or make zero
        float shadowFactor = inShadow ? 0.0f : 1.0f;

        finalColor += baseColor * NdotL * shadowFactor;
    }

    return finalColor;
}
