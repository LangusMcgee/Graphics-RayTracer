
#include "GCP_GFX_Framework.h"
#include <iostream>
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"
//#include "helpful.h"


int main(int argc, char* argv[])
{
	// Set window size
	glm::ivec2 winSize(250, 250);

	// This will handle rendering to screen
	GCP_Framework _myFramework;

	// Initialises SDL and OpenGL and sets up a framebuffer
	if (!_myFramework.Init(winSize))
	{
		return -1;
	}

	ray_tracer raytrcr;
	std::shared_ptr <Sphere> sphere;
	std::shared_ptr <Sphere> sphere2;
	std::shared_ptr <Sphere> sphere3;
	{

		sphere = std::make_shared<Sphere>(glm::vec3(0, 0, -5), glm::vec3(0, 0, 1), 1.0f);
		sphere2 = std::make_shared<Sphere>(glm::vec3(-2, 0, -6), glm::vec3(1, 0, 0), 1.0f);
		sphere3 = std::make_shared<Sphere>(glm::vec3(0, 0, -5), glm::vec3(1, 0, 0), 1.0f);
		raytrcr.addSphere(sphere);
		raytrcr.addSphere(sphere2);
		raytrcr.addSphere(sphere3);
	}

	_myFramework.SetAllPixels(glm::vec3(0.1f, 0.1f, 1.0f));

	Camera cam;
	cam.setResolution(winSize.x, winSize.y);
	glm::vec3 rotati(-1, 0, 1);

	//cam.transform.rotation(rotati);

	//print_vec3(sphere->position());
	for (int i = 0; i < 20; i++)
	{
		//cam.transform.translate(rotati);
		//cam.transform.rotate(rotati);
		for (int i = 0; i < winSize.x; i++)
		{
			sphere->colour(glm::vec3(0, 1, 0));
			for (int j = 0; j < winSize.y; j++)
			{
				glm::vec3 colour = raytrcr.trace_ray(cam.createRay(glm::ivec2(i, j)));
				//std::cout << colour.x << " " << colour.y << " " << colour.z << "\n";
				_myFramework.DrawPixel(glm::ivec2(i, j), colour);
			}
		}
		_myFramework.RenderFrame();
	}




	// Preparing a position to draw a pixel
	glm::ivec2 pixelPosition = winSize / 2;

	// Preparing a colour to draw
	// Colours are RGB, each value ranges between 0 and 1
	glm::vec3 pixelColour(1, 0, 0);


	

	// Sets all pixels the same colour


	// Draws a single pixel
	//_myFramework.DrawPixel(pixelPosition, pixelColour);





	// Pushes the framebuffer to OpenGL and renders to screen
	// Also contains an event loop that keeps the window going until it's closed
	_myFramework.ShowAndHold();
	return 0;


}
