#include "Sphere.h"
#include "scene.h"
#include "helpful.h"
#include <iostream>

glm::vec3 surface::shade(glm::vec3 _viewPos, glm::vec3 _intersectPos, scene& _scene, int _recursion)
{
    _recursion--;
    glm::vec3 normal = get_normal(_intersectPos);

    glm::vec3 diffuse(0.0f);
    glm::vec3 ambient_colour = m_colour * 0.1f;

    int indirectSamples = _scene.indirectSamples;
    int shadowSamples = _scene.shadowSamples;

    // Iterate through lights
    for (int i = 0; i < _scene.light_list.size(); i++)
    {
        float lightContribution = 0.0f;

        // Accumulate light values from area light samples to get a soft shadow
        for (int s = 0; s < shadowSamples; s++)
        {
            // Set values for sample
            glm::vec3 lightPos = getRandomPointOnLight(_scene.light_list[i]);
            glm::vec3 lightDir = glm::normalize(lightPos - _intersectPos);
            float lightDist = glm::distance(lightPos, _intersectPos);

            // Create a ray from sphere to sample pos
            Ray shadowRay(_intersectPos + normal * 0.0001f, lightDir);

            if (!shadowRayTest(lightDist, _intersectPos, shadowRay, _scene))
            {
                // Add light to contribution if sample is not blocked
                lightContribution += glm::max(glm::dot(normal, lightDir), 0.0f);
            }
        }

        lightContribution /= shadowSamples; // get the mean value
        diffuse += m_colour * lightContribution * _scene.light_list[i]->color; // Apply to diffuse

    }

    // Indirect lighting (recursive)
    if (_recursion > 0 && indirectSamples > 0)
    { 
        glm::vec3 indirect_colour =
            getIndirectLighting(_intersectPos, normal, indirectSamples, _recursion, _scene);

        diffuse += indirect_colour * 0.5f;
    }

    return ambient_colour + diffuse;
}

bool surface::shadowRayTest(float lightDist, glm::vec3 _intersectPos, Ray _shadowRay, scene& _scene)
{
    glm::vec3 shadow_ray_intersect(0.0f);

    for (int x = 0; x < _scene.object_list.size(); x++)
    {
        // Test for intersection
        if (_scene.object_list[x]->intersect(_shadowRay, shadow_ray_intersect))
        {
            // Check if between ray origin and light pos
            float hitDist = glm::distance(_intersectPos, shadow_ray_intersect);
            if (hitDist < lightDist)
            {
                // if so its occluding making a shadow
                return true;
            }
        }
    }
    return false;
}

glm::vec3 surface::getIndirectLighting(glm::vec3 _pos, glm::vec3 _normal, int _samples, int _recursion, scene& _scene)
{
    glm::vec3 indirect(0.0f);

    // Take multiple random samples to reduce noise
    for (int i = 0; i < _samples; ++i)
    {
        // generate a random direction in a unitt sphere
        glm::vec3 randUnit = randomInUnitSphere();
        glm::vec3 dir = glm::normalize(_normal + randUnit);

        Ray ray(_pos + _normal * 0.001f, dir);

        glm::vec3 hitPos;
        float closest = FLT_MAX;

        // index of the closest hit object
        int hitIndex = -1;

        // Find  closest object hit by ray
        for (int i = 0; i < _scene.object_list.size(); i ++)
        {
            glm::vec3 temp;
            if (_scene.object_list[i]->intersect(ray, temp))
            {
                float d = glm::distance(_pos, temp);
                if (d < closest)
                {
                    closest = d;
                    hitIndex = i;
                    hitPos = temp;
                }
            }
        }

        // if no hit, skip
        if (hitIndex == -1)
            continue;

        glm::vec3 hitNormal = _scene.object_list[hitIndex]->get_normal(hitPos);

        // Add the direct lighting at the hit point
        indirect += _scene.object_list[hitIndex]->directLighting(hitPos, hitNormal, _scene);
    }

    // Return avg..
    return indirect / float(_samples);
}

// https://mathworld.wolfram.com/SpherePointPicking.html
glm::vec3 surface::getRandomPointOnLight(std::shared_ptr<light> _light)
{
    const float pi = 3.14159265358979323846f;

    // Create random uniform values
    float u = static_cast<float>(rand()) / RAND_MAX;
    float v = static_cast<float>(rand()) / RAND_MAX;

    // Convert random values into spherical coordinates
    float theta = u * 2.0f * pi;
    float phi = acos(2.0f * v - 1.0f);

    // Get coordinates
    float x = _light->radius * sin(phi) * cos(theta);
    float y = _light->radius * sin(phi) * sin(theta);
    float z = _light->radius * cos(phi);

    // translate point
    return glm::vec3(x, y, z) + _light->position;
}


glm::vec3 surface::directLighting(glm::vec3 intersectPos, glm::vec3 normal, scene& _scene)
{
    glm::vec3 result(0.0f);

    // Go through every light
    for (int i = 0; i < _scene.light_list.size(); i++)
    {
        // Setup light values
        glm::vec3 lightPos = getRandomPointOnLight(_scene.light_list[i]);
        glm::vec3 lightDir = glm::normalize(lightPos - intersectPos);
        float lightDist = glm::distance(lightPos, intersectPos);

        // Init ray
        Ray shadowRay(intersectPos + normal * 0.0001f, lightDir);

        // Test for intersection
        if (!shadowRayTest(lightDist, intersectPos, shadowRay, _scene))
        {
            float NdotL = glm::max(glm::dot(normal, lightDir), 0.0f);
            result += m_colour * _scene.light_list[i]->color * NdotL; // add to result
        }
    }

    return result;
}

glm::vec3 surface::randomInUnitSphere()
{
    // Returns a random point
    // trial and error until within unit sphere
    while (true)
    {
        glm::vec3 p
        (
            float(rand()) / RAND_MAX * 2.0f - 1.0f,
            float(rand()) / RAND_MAX * 2.0f - 1.0f,
            float(rand()) / RAND_MAX * 2.0f - 1.0f
        );

        if (glm::dot(p, p) < 1.0f)
            return p;
    }
}