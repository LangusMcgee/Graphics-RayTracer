#include "Sphere.h"
#include "scene.h"
#include "helpful.h"
#include <iostream>

glm::vec3 surface::shade(glm::vec3 _viewPos, glm::vec3 _intersectPos, scene& _scene, int _recursion)
{
    glm::vec3 normal = get_normal(_intersectPos);

    glm::vec3 diffuse = glm::vec3(0.0f);
    glm::vec3 specular = glm::vec3(0.0f);

    glm::vec3 shadow_ray_intersect;
    glm::vec3 ambient_colour = m_colour * 0.1f;

    int indirectSamples = 4;

    // iterate through each light
    for (int i = 0; i < _scene.light_list.size(); i++)
    {
        // get the light direction and distance
		glm::vec3 lightPos = _scene.light_list[i]->transform.position();

        glm::vec3 lightDir = normalize(lightPos - _intersectPos);
        float lightDist = glm::distance(lightPos, _intersectPos);

        // shadow ray
        Ray shadow_ray(_intersectPos + normal * 0.0001f, lightDir);

        // check for occluders
        bool inShadow = shadowRayTest(lightDist, _intersectPos, shadow_ray, _scene);

        // Indirect Lighting ---------------------------------------------------------------------------------------------------------------//
        if (inShadow)
        {
            if (_recursion > 0)
            {
                _recursion--;

                glm::vec3 indirect_colour = getIndirectLighting(_intersectPos, normal, indirectSamples, _recursion, _scene);

                //print_vec3(indirect_colour);
                diffuse += indirect_colour;
                diffuse /= 2;

                // in shadow - don't do anything
                //diffuse_contribution *= glm::vec3(0.2f);

            }


        }
        else
        {
            // not in shadow
            //diffuse += _scene.light_list[i]->color * _scene.light_list[i]->intensity;

            // diffuse
            float NdotL = glm::max(glm::dot(normal, lightDir), 0.0f);
            glm::vec3 diffuse_contribution = m_colour * NdotL;

            if (_recursion > 0)
            {
                _recursion--;

                glm::vec3 indirect_colour = getIndirectLighting(_intersectPos, normal, indirectSamples, _recursion, _scene);

                diffuse += indirect_colour;

                diffuse /= 2;
            }


            diffuse += diffuse_contribution * _scene.light_list[i]->color;



            // specular
            glm::vec3 viewDir = glm::normalize(_viewPos - _intersectPos);
            glm::vec3 reflectDir = reflect(-lightDir, normal);

            float spec = pow(glm::max(glm::dot(viewDir, reflectDir), 0.0f), 32.0f);
            glm::vec3 specularColor(_scene.light_list[i]->color);

            specular += spec * specularColor;

        }


    }

    // final color
    return ambient_colour + diffuse + specular;
}


bool surface::shadowRayTest(float lightDist, glm::vec3 _intersectPos, Ray _shadowRay, scene &_scene)
{
    glm::vec3 shadow_ray_intersect(0);
    // shadow ray

    // check for occluders
    for (int x = 0; x < _scene.object_list.size(); x++)
    {
        if (_scene.object_list[x].get() == this)
            continue;

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

glm::vec3 surface::getIndirectLighting(glm::vec3 _intersectPos, glm::vec3 _normal, int _samples, int _recursion, scene &_scene)
{
    glm::vec3 indirect_colour(0);
    for (int i = 0; i < _samples; i++)
    {
        float rx = static_cast <float>(rand()) / (static_cast <float>(RAND_MAX / 0.4) - 0.2);
        float ry = static_cast <float>(rand()) / (static_cast <float>(RAND_MAX / 0.4) - 0.2);
        float rz = static_cast <float>(rand()) / (static_cast <float>(RAND_MAX / 0.4) - 0.2);
        glm::vec3 indirect_direction = _normal + glm::vec3(rx, ry, rz);
        Ray indirectLighting(_intersectPos, indirect_direction);


        for (int x = 0; x < _scene.object_list.size(); x++)
        {
            if (_scene.object_list[x].get() == this)
                continue;
            glm::vec3 indirectIntersect(0);
            if (_scene.object_list[x]->intersect(indirectLighting, indirectIntersect))
            {
                indirect_colour += _scene.object_list[x]->shade(_normal, indirectIntersect, _scene, _recursion);
            }
        }
    }
    return indirect_colour /= _samples;
}