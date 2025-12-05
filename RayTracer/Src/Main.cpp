
#include "GCP_GFX_Framework.h"
#include <iostream>
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"
#include "Renderer.h"
#include "vector"
#include <thread>
//#include "helpful.h"


int main(int argc, char* argv[])
{
	renderer rendererA;
	rendererA.init(glm::vec2(500, 500));

	// Setup Objects /////////////////////////////////////////////////////////////////////////////
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

		// add to raytracer object list
		rendererA.addObject(sphere);
		rendererA.addObject(sphere2);
		rendererA.addObject(sphere3);
		rendererA.addObject(ground);

		rendererA.renderScene();
	}


	return 0;


}
