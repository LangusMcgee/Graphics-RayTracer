
#include "GCP_GFX_Framework.h"
#include <iostream>
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"
//#include "helpful.h"


int main(int argc, char* argv[])
{
	int winX = 500;
	int winY = 500;
	// Set window size
	glm::ivec2 winSize(winX, winY);

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

		sphere = std::make_shared<Sphere>(glm::vec3(winX / 1.5, winY / 2, -400), glm::vec3(0, 0, 1), 40);
		sphere2 = std::make_shared<Sphere>(glm::vec3(winX / 3, winY / 2, -500), glm::vec3(1, 0, 0), 60);
		sphere3 = std::make_shared<Sphere>(glm::vec3(winX / 2, -100, -1000), glm::vec3(0, 1, 0), 500);
		raytrcr.addSphere(sphere);
		raytrcr.addSphere(sphere2);
		raytrcr.addSphere(sphere3);
	}

	_myFramework.SetAllPixels(glm::vec3(0.1f, 0.1f, 0.3f));

	Camera cam;

	//print_vec3(sphere->position());

	float r = 0.2;
	for (int i = 0; i < winX; i++)
	{
		sphere->colour(glm::vec3(0, 1, 0));
		for (int j = 0; j < winY; j++)
		{
			sphere->colour(glm::vec3(r, r, 1));
			glm::vec3 colour = raytrcr.trace_ray(cam.createRay(glm::ivec2(i, j)));
			//std::cout << colour.x << " " << colour.y << " " << colour.z << "\n";
			_myFramework.DrawPixel(glm::ivec2(i,j), colour);
		}
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
