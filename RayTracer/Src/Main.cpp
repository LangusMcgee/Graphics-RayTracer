
#include "GCP_GFX_Framework.h"
#include <iostream>
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"
#include "Renderer.h"
#include <thread>
//#include "helpful.h"


int main(int argc, char* argv[])
{
	unsigned int n = std::thread::hardware_concurrency();
	std::cout << n << " concurrent threads are supported.\n";



	// Initialise window //////////////////////////////////////////
	glm::ivec2 winSize(300, 300);

	// This will handle rendering to screen
	GCP_Framework _myFramework;

	// Initialises SDL and OpenGL and sets up a framebuffer
	if (!_myFramework.Init(winSize))
	{
		return -1;
	}
	//////////////////////////////////////////////////////////////


	ray_tracer raytrcr;


	// Setup Objects /////////////////////////////////////////////////////////////////////////////
	std::shared_ptr <Sphere> sphere;
	std::shared_ptr <Sphere> sphere2;
	std::shared_ptr <Sphere> sphere3;
	{

		// create objects
		sphere = std::make_shared<Sphere>(glm::vec3(0, 0, -5), glm::vec3(0, 0, 1), 1.0f);
		sphere2 = std::make_shared<Sphere>(glm::vec3(-2, 0, -6), glm::vec3(1, 0, 0), 1.0f);
		sphere3 = std::make_shared<Sphere>(glm::vec3(3, 0, -5), glm::vec3(1, 0, 0), 1.0f);

		// add to raytracer object list
		raytrcr.addSphere(sphere);
		raytrcr.addSphere(sphere2);
		raytrcr.addSphere(sphere3);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////

	// set to pink because its better than nothing.
	_myFramework.SetAllPixels(glm::vec3(1.0f, 0.0f, 1.0f));
	_myFramework.RenderFrame();

	Camera camera;
	camera.setResolution(winSize.x, winSize.y);
	glm::vec3 rotati(-1, 0, 1);


	// RENDER LOOP /////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < 20; i++)
	{
		// Iterate through x and y axis using nested loop.
		for (int i = 0; i < winSize.x; i++)
		{
			for (int j = 0; j < winSize.y; j++)
			{
				// Determine pixel colour
				glm::vec3 colour = raytrcr.trace_ray(camera.createRay(glm::ivec2(i, j)));

				// Draws shaded pixel
				_myFramework.DrawPixel(glm::ivec2(i, j), colour);
			}
		}
		_myFramework.RenderFrame();
		// todo
		// ensure window close works
	}
	/////////////////////////////////////////////////////////////////////////////////////////////

	return 0;


}
