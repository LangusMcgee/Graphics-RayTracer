#include "Sphere.h"
#include "scene.h"
#include "helpful.h"
#include <iostream>

glm::vec3 surface::shade(glm::vec3 _viewPos, glm::vec3 _intersectPos, scene& _scene, int _recursion)
{
    glm::vec3 normal = get_normal(_intersectPos);

    glm::vec3 diffuse(0.0f);
    glm::vec3 ambient_colour = m_colour * 0.1f;

    int indirectSamples = 4;
    int shadowSamples = 4;

    // Iterate through lights
    for (int i = 0; i < _scene.light_list.size(); i++)
    {
        float lightContribution = 0.0f;

        for (int s = 0; s < shadowSamples; s++)
        {
            glm::vec3 lightPos = getRandomPointOnLight(_scene.light_list[i]);
            glm::vec3 lightDir = glm::normalize(lightPos - _intersectPos);
            float lightDist = glm::distance(lightPos, _intersectPos);

            Ray shadowRay(_intersectPos + normal * 0.0001f, lightDir);

            if (!shadowRayTest(lightDist, _intersectPos, shadowRay, _scene))
            {
                lightContribution += glm::max(glm::dot(normal, lightDir), 0.0f);
            }
        }

        lightContribution /= shadowSamples;
        diffuse += m_colour * lightContribution * _scene.light_list[i]->color;

    }

    // Indirect lighting (recursive)
    if (_recursion > 0)
    {
        _recursion--;
        glm::vec3 indirect_colour =
            getIndirectLighting(_intersectPos, normal, indirectSamples, _recursion, _scene);

        diffuse += indirect_colour;
        diffuse *= 0.5f;
    }

    return ambient_colour + diffuse;
}

bool surface::shadowRayTest(float lightDist, glm::vec3 _intersectPos, Ray _shadowRay, scene& _scene)
{
    glm::vec3 shadow_ray_intersect(0.0f);

    for (int x = 0; x < _scene.object_list.size(); x++)
    {
        if (_scene.object_list[x]->intersect(_shadowRay, shadow_ray_intersect))
        {
            float hitDist = glm::distance(_intersectPos, shadow_ray_intersect);
            if (hitDist < lightDist)
            {
                return true;
            }
        }
    }
    return false;
}

glm::vec3 surface::getIndirectLighting(
    glm::vec3 _intersectPos,
    glm::vec3 _normal,
    int _samples,
    int _recursion,
    scene& _scene)
{
    glm::vec3 indirect_colour(0.0f);

    for (int i = 0; i < _samples; i++)
    {
        // --- Cosine-weighted hemisphere sampling ---
        float r1 = float(rand()) / RAND_MAX;
        float r2 = float(rand()) / RAND_MAX;

        float phi = 2.0f * 3.1415926535f * r1;
        float cosTheta = sqrt(1.0f - r2);
        float sinTheta = sqrt(r2);

        // Tangent space basis
        glm::vec3 tangent;

        if (fabs(_normal.x) > 0.1f)
            tangent = glm::cross(glm::vec3(0, 1, 0), _normal);
        else
            tangent = glm::cross(glm::vec3(1, 0, 0), _normal);

        tangent = glm::normalize(tangent);


        glm::vec3 bitangent = glm::cross(_normal, tangent);

        glm::vec3 direction = glm::normalize(tangent * cos(phi) * sinTheta + bitangent * sin(phi) * sinTheta + _normal * cosTheta);

        Ray indirectRay(_intersectPos + _normal * 0.0001f, direction);

        // --- Find closest intersection ---
        surface* hitObject = nullptr;
        glm::vec3 hitPos;
        float closestDist = std::numeric_limits<float>::max();

        for (auto& obj : _scene.object_list)
        {
            glm::vec3 tempHit;
            if (obj->intersect(indirectRay, tempHit))
            {
                float d = glm::distance(_intersectPos, tempHit);
                if (d < closestDist)
                {
                    closestDist = d;
                    hitObject = obj.get();
                    hitPos = tempHit;
                }
            }
        }

        if (!hitObject)
            continue;

        // --- Bounce direct lighting from hit surface ---
        glm::vec3 hitNormal = hitObject->get_normal(hitPos);

        glm::vec3 directAtHit = hitObject->directLighting(hitPos, hitNormal, _scene);

        // Lambertian BRDF (albedo / pi)
        indirect_colour += directAtHit * hitObject->m_colour;
    }

    return indirect_colour / static_cast<float>(_samples);
}

// https://mathworld.wolfram.com/SpherePointPicking.html
glm::vec3 surface::getRandomPointOnLight(std::shared_ptr<light> _light)
{
    float pi = 3.14159265358979323846f;

    float u = static_cast<float>(rand()) / RAND_MAX;
    float v = static_cast<float>(rand()) / RAND_MAX;

    float theta = u * 2.0f * pi;
    float phi = acos(2.0f * v - 1.0f);

    float x = _light->radius * sin(phi) * cos(theta);
    float y = _light->radius * sin(phi) * sin(theta);
    float z = _light->radius * cos(phi);

    return glm::vec3(x, y, z) + _light->transform.position();
}


glm::vec3 surface::directLighting(
    glm::vec3 intersectPos,
    glm::vec3 normal,
    scene& _scene)
{
    glm::vec3 result(0.0f);

    for (auto& light : _scene.light_list)
    {
        glm::vec3 lightPos = getRandomPointOnLight(light);
        glm::vec3 lightDir = glm::normalize(lightPos - intersectPos);
        float lightDist = glm::distance(lightPos, intersectPos);

        Ray shadowRay(intersectPos + normal * 0.0001f, lightDir);

        if (!shadowRayTest(lightDist, intersectPos, shadowRay, _scene))
        {
            float NdotL = glm::max(glm::dot(normal, lightDir), 0.0f);
            result += m_colour * light->color * NdotL;
        }
    }

    return result;
}