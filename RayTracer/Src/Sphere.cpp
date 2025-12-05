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
	//uniform sample u_Texture;
	//glm::vec3 u_ViewPos;

	//varying vec2 v_TexCoord;
	glm::vec3 normal = get_normal(_intersectPos);

	//vec4 tex = texture2D(u_Texture, v_TexCoord);
	glm::vec3 lightPos(0, 0, 10);
	//lightPos = _scene.light_list[0]->position;
	glm::vec3 diffuseColor = m_colour;

	bool inShadow = false;


	glm::vec3 shadowRayIntersect;

	for (int i = 0; i < _scene.light_list.size(); i++)
	{
		glm::vec3 lightDir = normalize(_scene.light_list[i]->position - _intersectPos);

		float lightDist = glm::distance(_scene.light_list[i]->position, _intersectPos);

		for (int x = 0; x < _scene.object_list.size(); x++)
		{
			if (_scene.object_list[x].get() == this)
				continue;   // skip self

			Ray shadowRay(_intersectPos + normal * 0.0001f, lightDir);

			if (_scene.object_list[x]->intersect(shadowRay, shadowRayIntersect))
			{
				float hitDist = glm::distance(_intersectPos, shadowRayIntersect);

				if (hitDist < lightDist)
				{
					inShadow = true;
					return glm::vec3(0);
					break;
				}
			}
		}
	}
	glm::vec3 lightDir = normalize(lightPos - _intersectPos);

	float diff = std::fmax(dot(normal, lightDir), 0.1);
	glm::vec3 diffuse = diffuseColor * diff;

	glm::vec3 specularColor(1, 1, 0.5);

	glm::vec3 viewDir = glm::normalize(_viewPos - _intersectPos);
	glm::vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(std::fmax(dot(viewDir, reflectDir), 0.0), 32.0);
	glm::vec3 specular = spec * specularColor;

	return diffuse + specular;
}