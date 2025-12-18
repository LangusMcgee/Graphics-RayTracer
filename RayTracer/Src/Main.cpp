
#include <iostream>
#include <thread>

#include "GCP_GFX_Framework.h"
#include "Sphere.h"
#include "Renderer.h"


int main(int argc, char* argv[])
{
	renderer rendererA;
	rendererA.init(glm::vec2(500, 500));


	//int threadAmount = 0;
	//bool correctVal = false;
	//while (!correctVal)
	//{
	//	std::cout << "How many cores?: ";
	//	while (!(std::cin >> threadAmount))
	//	{
	//		std::cout << "Please enter a valid integer: ";

	//		std::cin.clear();
	//		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//	}

	//	correctVal = rendererA.set_thread_usage(int(threadAmount));
	//}
	rendererA.set_thread_usage(12);

	// Setup Camera /////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<Camera> camera;
	camera = std::make_shared<Camera>();

	rendererA.set_cam(camera);

	camera->transform.rotate(glm::vec3(-25, -25, 0));
	camera->transform.translate(glm::vec3(-11, 10, 0));

	// Setup Objects /////////////////////////////////////////////////////////////////////////////
	scene main_scene;

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
		(glm::vec3(0, -1001, -21), glm::vec3(1, 1, 1), 1000.0f);

	// Add to scene
	main_scene.object_list.push_back(sphere1);
	main_scene.object_list.push_back(sphere2);
	main_scene.object_list.push_back(sphere3);
	main_scene.object_list.push_back(sphere4);
	main_scene.object_list.push_back(ground);

	std::shared_ptr<light> light1;
	std::shared_ptr<light> light2;
	std::shared_ptr<light> light3;
	
	// Create lights
	light1 = std::make_shared<light>(glm::vec3(100, 21, -21), glm::vec3(0, 0, 1), 0.2f);
	light2 = std::make_shared<light>(glm::vec3(-20, 0, -10), glm::vec3(1, 1, 0), 0.2f);
	light3 = std::make_shared<light>(camera->transform.position(), glm::vec3(1, 1, 0.6), 0.2f);

	// Add to scene
	main_scene.light_list.push_back(light1);
	main_scene.light_list.push_back(light2);
	main_scene.light_list.push_back(light3);

	rendererA.set_scene(main_scene);
	// add to raytracer object list
		
	//for (int i = 1; i <= 20; i++) - used for testing different thread amounts
	//{
	//	rendererA.set_thread_usage(i);
	//	rendererA.renderScene();
	//}
	int testRange = 8;
	int series = 3;

	//std::cout << "----------ANTI ALIASING----------\n";
	//for (int x = 1; x <= series; x++)
	//{
	//	std::cout << "Test " << x << "\n";
	//	for (int i = 1; i <= testRange; i++)
	//	{
	//		std::cout << i << " AA samples.\n";
	//		rendererA.setAASamples(i);

	//		rendererA.renderScene();
	//	}
	//}
	rendererA.renderScene();
	//rendererA.setAASamples(1);

	//std::cout << "----------Shadow Samples----------\n";
	//for (int x = 1; x <= series; x++)
	//{
	//	std::cout << "Test " << x << "\n";
	//	for (int i = 1; i <= testRange; i++)
	//	{
	//		std::cout << i << " Shadow samples.\n";
	//		main_scene.shadowSamples = i;
	//		rendererA.set_scene(main_scene);
	//		rendererA.renderScene();
	//	}
	//}

	//main_scene.shadowSamples = 0;

	//std::cout << "----------Indirect Samples----------\n";
	//for (int x = 1; x <= series; x++)
	//{
	//	std::cout << "Test " << x << "\n";
	//	for (int i = 1; i <= testRange; i++)
	//	{
	//		std::cout << i << " Indirect samples.\n";
	//		main_scene.indirectSamples = i;
	//		rendererA.set_scene(main_scene);
	//		rendererA.renderScene();
	//	}
	//}


	rendererA.show();


	return 0;


}
