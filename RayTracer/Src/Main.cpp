
#include <iostream>
#include <thread>

#include "GCP_GFX_Framework.h"
#include "Sphere.h"
#include "Renderer.h"


int main(int argc, char* argv[])
{
	renderer Renderer;
	Renderer.init(glm::vec2(750, 750));

	Renderer.set_thread_usage(18);

	// Setup Camera /////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<Camera> camera;
	camera = std::make_shared<Camera>();

	Renderer.set_cam(camera);

	camera->transform.rotate(glm::vec3(-25, -25, 0));
	camera->transform.translate(glm::vec3(-11, 10, 0));

	// Setup Objects /////////////////////////////////////////////////////////////////////////////
	scene Scene;

	Scene.shadowSamples = 4;
	Scene.indirectSamples = 4;
	Renderer.setAASamples(6);

	std::shared_ptr <Sphere> sphere1;
	std::shared_ptr <Sphere> sphere2;
	std::shared_ptr <Sphere> sphere3;
	std::shared_ptr <Sphere> sphere4;
	std::shared_ptr <Sphere> ground;

	// create objects
	sphere1 = std::make_shared<Sphere>
		(glm::vec3(0, 1, -21), glm::vec3(1, 1, 1), 2.0f);
	sphere2 = std::make_shared<Sphere>
		(glm::vec3(-3, 0, -21), glm::vec3(1, 0, 0), 1.0f);
	sphere3 = std::make_shared<Sphere>
		(glm::vec3(3, 0, -21), glm::vec3(1, 1, 0), 1.0f);
	sphere4 = std::make_shared<Sphere>
		(glm::vec3(0.3, 0, -18), glm::vec3(0, 1, 1), 1.0f);
	ground = std::make_shared<Sphere>
		(glm::vec3(0, -1001, -21), glm::vec3(0.2, 0.6, 0.2), 1000.0f);

	// Add to scene
	Scene.object_list.push_back(sphere1);
	Scene.object_list.push_back(sphere2);
	Scene.object_list.push_back(sphere3);
	Scene.object_list.push_back(sphere4);
	Scene.object_list.push_back(ground);

	std::shared_ptr<light> light1;
	std::shared_ptr<light> light2;
	std::shared_ptr<light> light3;
	
	// Create lights
	light1 = std::make_shared<light>(glm::vec3(30, 21, -30), glm::vec3(1, 1, 1), 1.0f);
	light2 = std::make_shared<light>(glm::vec3(-20, 0, -10), glm::vec3(0.7, 0.7, 0), 0.2f);
	light3 = std::make_shared<light>(camera->transform.position(), glm::vec3(0.2, 0.2, 0.2), 0.2f);

	// Add to scene
	Scene.light_list.push_back(light1);
	Scene.light_list.push_back(light2);
	//Scene.light_list.push_back(light3);


	Renderer.set_scene(Scene);
	// add to raytracer object list
		
	//for (int i = 1; i <= 20; i++)// - used for testing different thread amounts
	//{
	//	rendererA.set_thread_usage(i);
	//	rendererA.renderScene();
	//}


////	----------------------- automated test runs ----------------------------------//
//
//	int testRange = 8;
//	int series = 3;
//
//	std::cout << "----------ANTI ALIASING----------\n";
//	for (int x = 1; x <= series; x++)
//	{
//		std::cout << "Test " << x << "\n";
//		for (int i = 1; i <= testRange; i++)
//		{
//			std::cout << i << " AA samples.\n";
//			rendererA.setAASamples(i);
//
//			rendererA.renderScene();
//		}
//	}
//
//	rendererA.setAASamples(1);
//
//	std::cout << "----------Shadow Samples----------\n";
//	for (int x = 1; x <= series; x++)
//	{
//		std::cout << "Test " << x << "\n";
//		for (int i = 1; i <= testRange; i++)
//		{
//			std::cout << i << " Shadow samples.\n";
//			main_scene.shadowSamples = i;
//			rendererA.set_scene(main_scene);
//			rendererA.renderScene();
//		}
//	}
//
//	main_scene.shadowSamples = 0;
//
//	std::cout << "----------Indirect Samples----------\n";
//	for (int x = 1; x <= series; x++)
//	{
//		std::cout << "Test " << x << "\n";
//		for (int i = 1; i <= testRange; i++)
//		{
//			std::cout << i << " Indirect samples.\n";
//			main_scene.indirectSamples = i;
//			rendererA.set_scene(main_scene);
//			rendererA.renderScene();
//		}
//	}
//
//	/////////////////////////////////////////////////////////////////////////////////////////////////
	Renderer.renderScene();
	Renderer.show();


	return 0;


}
