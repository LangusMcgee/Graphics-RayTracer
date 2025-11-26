
#include "GCP_GFX_Framework.h"
#include <iostream>
#include "RayTracer.h"
#include "Sphere.h"
#include "Camera.h"


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

	{
		Sphere s1(glm::vec3(winX / 2, winY / 2, -400), glm::vec3(0,0,1), 40);
		raytrcr.addSphere(s1);
	}

	_myFramework.SetAllPixels(glm::vec3(0.1f, 0.1f, 0.3f));

	Camera cam;

	glm::vec3 debug_red(1, 0, 0);

	for (int i = 0; i < winX; i++)
	{
		for (int j = 0; j < winY; j++)
		{
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
