#include "Sphere.h"

bool Sphere::intersect(Ray _ray, glm::vec3 &_intersectPos)
{
	glm::vec3 p = m_position; // Sphere position
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
	return glm::normalize(_intersectPos - m_position);
}


glm::vec3 Sphere::shade(glm::vec3 _viewPos, glm::vec3 _hitPos)
{
	//uniform sample u_Texture;
	glm::vec3 u_ViewPos;

	//varying vec2 v_TexCoord;
	glm::vec3 v_Normal = get_normal(_hitPos);
	glm::vec3 v_FragPos = _hitPos;

	//vec4 tex = texture2D(u_Texture, v_TexCoord);
	glm::vec3 lightPos(10, 10, 10);
	glm::vec3 diffuseColor(1, 0, 0);

	glm::vec3 N = normalize(v_Normal);
	glm::vec3 lightDir = normalize(lightPos - v_FragPos);
	float diff = std::fmax(dot(N, lightDir), 0.0);
	glm::vec3 diffuse = diffuseColor * diff;

	glm::vec3 specularColor(1, 1, 1);

	glm::vec3 viewDir = glm::normalize(u_ViewPos - v_FragPos);
	glm::vec3 reflectDir = reflect(-lightDir, N);
	float spec = pow(std::fmax(dot(viewDir, reflectDir), 0.0), 32.0);
	glm::vec3 specular = spec * specularColor;

	return diffuse + specular;
}