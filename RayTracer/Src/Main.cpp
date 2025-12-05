
#include "GCP_GFX_Framework.h"
#include <iostream>
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"
#include "Renderer.h"
#include "vector"
#include "scene.h"
#include <thread>
//#include "helpful.h"


int main(int argc, char* argv[])
{
	renderer rendererA;
	rendererA.init(glm::vec2(500, 500));

	// Setup Objects /////////////////////////////////////////////////////////////////////////////
	scene main_scene;

	std::shared_ptr <Sphere> sphere;
	std::shared_ptr <Sphere> sphere2;
	std::shared_ptr <Sphere> sphere3;
	std::shared_ptr <Sphere> ground;
	{

		// create objects
		sphere = std::make_shared<Sphere>
			(glm::vec3(0, 0, -21), glm::vec3(0, 0, 1), 1.0f);

		sphere2 = std::make_shared<Sphere>
			(glm::vec3(-2, 0, -20), glm::vec3(1, 0, 0), 1.0f);

		sphere3 = std::make_shared<Sphere>
			(glm::vec3(3, 0, -22), glm::vec3(1, 0, 0), 1.0f);

		ground = std::make_shared<Sphere>
			(glm::vec3(0, -100, -100), glm::vec3(0.3, 0.6, 0.3), 100.0f);

		main_scene.object_list.push_back(sphere);
		main_scene.object_list.push_back(sphere2);
		main_scene.object_list.push_back(sphere3);
		main_scene.object_list.push_back(ground);

		std::shared_ptr<light> light1;

		light1 = std::make_shared<light>(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), 1.0f);

		light1->position = glm::vec3(1, 0, 0);

		main_scene.light_list.push_back(light1);

		rendererA.set_scene(main_scene);
		// add to raytracer object list

		rendererA.renderScene();
	}


	return 0;


}
